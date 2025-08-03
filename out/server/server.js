"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const node_1 = require("vscode-languageserver/node");
const vscode_languageserver_textdocument_1 = require("vscode-languageserver-textdocument");
const child_process_1 = require("child_process");
const path_1 = require("path");
// Create LSP connection
// With this explicit stdio connection:
const connection = (0, node_1.createConnection)(node_1.ProposedFeatures.all, process.stdin, // STDIN
process.stdout // STDOUT
);
const documents = new node_1.TextDocuments(vscode_languageserver_textdocument_1.TextDocument);
documents.onDidOpen(() => {
    connection.console.log('Document opened!');
});
// Start compiler process
const compilerPath = (0, path_1.join)(__dirname, '../../compiler/bolt');
const compilerProcess = (0, child_process_1.spawn)(compilerPath, ['--language-server']);
process.stdin.on('data', (chunk) => {
    console.error('Received raw input:', chunk.toString());
});
// Handle compiler stdout
compilerProcess.stdout?.on('data', (data) => {
    try {
        const response = JSON.parse(data.toString());
        if (response.uri && response.diagnostics) {
            connection.sendDiagnostics({
                uri: response.uri,
                diagnostics: response.diagnostics
            });
        }
    }
    catch (err) {
        connection.console.error(`Failed to parse compiler output: ${err}`);
    }
});
// Handle errors
compilerProcess.stderr?.on('data', (data) => {
    connection.console.error(`Compiler error: ${data.toString()}`);
});
compilerProcess.on('error', (err) => {
    connection.console.error(`Compiler process error: ${err.message}`);
});
compilerProcess.on('exit', (code) => {
    connection.console.log(`Compiler process exited with code ${code}`);
});
// Initialize handler
connection.onInitialize((params) => {
    return {
        capabilities: {
            textDocumentSync: node_1.TextDocumentSyncKind.Incremental,
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
    }
    catch (err) {
        connection.console.error(`Failed to send validation request: ${err}`);
    }
});
// Cleanup on exit
const disposables = [];
process.on('exit', () => {
    compilerProcess.kill();
    disposables.forEach(d => d.dispose());
});
// Start listening
documents.listen(connection);
connection.listen();
//# sourceMappingURL=server.js.map