import {
    createConnection,
    TextDocuments,
    ProposedFeatures,
    InitializeParams,
    TextDocumentSyncKind,
    InitializeResult,
    Disposable,
    Diagnostic,
    IPCMessageReader,
    IPCMessageWriter
} from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { spawn, ChildProcess } from 'child_process';
import { join } from 'path';

// Create LSP connection
// With this explicit stdio connection:
const connection = createConnection(
    ProposedFeatures.all,
    process.stdin,   // STDIN
    process.stdout   // STDOUT
);

const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

documents.onDidOpen(() => {
    connection.console.log('Document opened!');
});
// Start compiler process
const compilerPath = join(__dirname, '../../compiler/bolt');
const compilerProcess: ChildProcess = spawn(compilerPath, ['--language-server']);

process.stdin.on('data', (chunk) => {
    console.error('Received raw input:', chunk.toString());
});

// Handle compiler stdout
compilerProcess.stdout?.on('data', (data: Buffer) => {
    try {
        const response = JSON.parse(data.toString());
        if (response.uri && response.diagnostics) {
            connection.sendDiagnostics({
                uri: response.uri,
                diagnostics: response.diagnostics
            });
            console.error(response.diagnostics);
        }
    } catch (err) {
        connection.console.error(`Failed to parse compiler output: ${err}`);
    }
});

// Handle errors
compilerProcess.stderr?.on('data', (data: Buffer) => {
    connection.console.error(`Compiler error: ${data.toString()}`);
});

compilerProcess.on('error', (err) => {
    connection.console.error(`Compiler process error: ${err.message}`);
});

compilerProcess.on('exit', (code) => {
    connection.console.log(`Compiler process exited with code ${code}`);
});

// Initialize handler
connection.onInitialize((params: InitializeParams): InitializeResult => {
    return {
        capabilities: {
            textDocumentSync: TextDocumentSyncKind.Incremental,
            // Add more capabilities as needed
        }
    };
});

// Document change handler
documents.onDidChangeContent((change) => {
    const text = change.document.getText();
    try {
        compilerProcess.stdin?.write(JSON.stringify({
            command: 'validate',
            text: text,
            uri: change.document.uri
        }) + '\n');
    } catch (err) {
        connection.console.error(`Failed to send validation request: ${err}`);
    }
});

// Cleanup on exit
const disposables: Disposable[] = [];
process.on('exit', () => {
    compilerProcess.kill();
    disposables.forEach(d => d.dispose());
});

// Start listening
documents.listen(connection);
connection.listen();