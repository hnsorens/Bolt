import { spawn, ChildProcess } from 'child_process';
import { join } from 'path';
import { Diagnostic } from 'vscode-languageserver/node';

export interface CompilerInterface {
    validate(uri: string, text: string): void;
    onDiagnostics(callback: (uri: string, diagnostics: Diagnostic[]) => void): void;
    dispose(): void;
}

export function startCompiler(): CompilerInterface {
    const compilerPath = join(__dirname, '../../compiler/bolt');
    const process = spawn(compilerPath, ['--language-server']);
    const callbacks: Array<(uri: string, diagnostics: Diagnostic[]) => void> = [];

    process.stdout?.on('data', (data: Buffer) => {
        const strData = data.toString();
        try {
            const response = JSON.parse(strData);
            if (response.uri && response.diagnostics) {
                callbacks.forEach(cb => cb(response.uri, response.diagnostics));
            }
        } catch (err) {
            console.error('Failed to parse compiler output:', err, '\nData:', strData);
        }
    });

    process.stderr?.on('data', (data: Buffer) => {
        console.error('Compiler error:', data.toString());
    });

    process.on('exit', (code) => {
        console.log(`Compiler process exited with code ${code}`);
    });

    return {
        validate(uri: string, text: string) {
            process.stdin?.write(JSON.stringify({
                command: 'validate',
                uri,
                text
            }) + '\n');
        },
        onDiagnostics(callback: (uri: string, diagnostics: Diagnostic[]) => void) {
            callbacks.push(callback);
        },
        dispose() {
            process.kill();
        }
    };
}