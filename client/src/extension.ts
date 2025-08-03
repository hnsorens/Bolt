import * as path from 'path';
import * as vscode from 'vscode';
import { LanguageClient, LanguageClientOptions, ServerOptions, TransportKind } from 'vscode-languageclient/node';

let client: LanguageClient;

export async function activate(context: vscode.ExtensionContext) {
    const serverModule = context.asAbsolutePath(
        path.join('out', 'server', 'server.js')
    );

    console.log('Starting language server at:', serverModule);

    const serverOptions: ServerOptions = {
        run: {
            command: 'node',
            args: [serverModule, '--stdio'],
            transport: TransportKind.stdio
        },
        debug: {
            command: 'node',
            args: [
                '--inspect=6009',
                serverModule,
                '--stdio'
            ],
            transport: TransportKind.stdio
        }
    };

   const clientOptions: LanguageClientOptions = {
        documentSelector: [{ scheme: 'file', language: 'bolt' }],
        outputChannel: vscode.window.createOutputChannel('Bolt Output')
    };

    client = new LanguageClient(
        'boltLanguageServer',
        'Bolt Language Server',
        serverOptions,
        clientOptions
    );

    try {
        // Proper async startup with error handling
        await client.start();
        console.log('Language client started successfully');
    } catch (err) {
        console.error('Failed to start language server:', err);
        vscode.window.showErrorMessage(
            `Bolt extension failed to start: ${err instanceof Error ? err.message : String(err)}`
        );
    }
}

export function deactivate(): Thenable<void> | undefined {
    return client?.stop();
}