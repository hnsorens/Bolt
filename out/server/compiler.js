"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.startCompiler = startCompiler;
const child_process_1 = require("child_process");
const path_1 = require("path");
function startCompiler() {
    const compilerPath = (0, path_1.join)(__dirname, '../../compiler/bolt');
    const process = (0, child_process_1.spawn)(compilerPath, ['--language-server']);
    const callbacks = [];
    process.stdout?.on('data', (data) => {
        const strData = data.toString();
        try {
            const response = JSON.parse(strData);
            if (response.uri && response.diagnostics) {
                callbacks.forEach(cb => cb(response.uri, response.diagnostics));
            }
        }
        catch (err) {
            console.error('Failed to parse compiler output:', err, '\nData:', strData);
        }
    });
    process.stderr?.on('data', (data) => {
        console.error('Compiler error:', data.toString());
    });
    process.on('exit', (code) => {
        console.log(`Compiler process exited with code ${code}`);
    });
    return {
        validate(uri, text) {
            process.stdin?.write(JSON.stringify({
                command: 'validate',
                uri,
                text
            }) + '\n');
        },
        onDiagnostics(callback) {
            callbacks.push(callback);
        },
        dispose() {
            process.kill();
        }
    };
}
//# sourceMappingURL=compiler.js.map