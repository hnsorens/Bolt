import {
    createConnection,
    TextDocuments,
    ProposedFeatures,
    InitializeParams,
    TextDocumentSyncKind,
    InitializeResult,
    Disposable,
    Diagnostic
} from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { spawn, ChildProcess } from 'child_process';
import { join } from 'path';

// Create LSP connection over stdio
const connection = createConnection(
    ProposedFeatures.all,
    process.stdin,
    process.stdout
);

const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

// Spawn your compiler process
const compilerPath = join(__dirname, '../../compiler/bolt');
const compilerProcess: ChildProcess = spawn(compilerPath, ['--language-server']);

// Buffer for incoming data from process.stdin to reconstruct full LSP messages
let inputBuffer = '';

// Helper: try parse and process full messages in the buffer
function tryProcessMessages() {
    while (true) {
        const headerEnd = inputBuffer.indexOf('\r\n\r\n');
        if (headerEnd === -1) break; // incomplete headers, wait for more data

        const headers = inputBuffer.slice(0, headerEnd).split('\r\n');
        let contentLength = 0;

        for (const header of headers) {
            const parts = header.split(':');
            if (parts[0].toLowerCase() === 'content-length') {
                contentLength = parseInt(parts[1].trim(), 10);
                break;
            }
        }

        if (contentLength === 0) {
            console.error('Content-Length header missing or invalid');
            break;
        }

        const totalMessageLength = headerEnd + 4 + contentLength; // 4 = length of \r\n\r\n

        if (inputBuffer.length < totalMessageLength) break; // incomplete message body

        const jsonString = inputBuffer.slice(headerEnd + 4, totalMessageLength);

        // Remove processed message from buffer
        inputBuffer = inputBuffer.slice(totalMessageLength);

        try {
            const json = JSON.parse(jsonString);
            // Forward full JSON message string (without headers) to compiler stdin
            compilerProcess.stdin?.write(JSON.stringify(json) + '\n');
        } catch (err) {
            console.error('Failed to parse JSON:', err);
        }
    }
}

// Listen to stdin data, buffer it and process complete messages
process.stdin.on('data', (chunk) => {
    inputBuffer += chunk.toString();
    tryProcessMessages();
});

// Forward diagnostics from compiler stdout to LSP client
let compilerStdoutBuffer = '';
compilerProcess.stdout?.on('data', (chunk: Buffer) => {
    compilerStdoutBuffer += chunk.toString();

    // Try to parse multiple JSON messages (assuming they are newline separated)
    let newlineIndex;
    while ((newlineIndex = compilerStdoutBuffer.indexOf('\n')) !== -1) {
        const messageStr = compilerStdoutBuffer.slice(0, newlineIndex).trim();
        compilerStdoutBuffer = compilerStdoutBuffer.slice(newlineIndex + 1);

        if (!messageStr) continue;

        try {
            const message = JSON.parse(messageStr);
            if (message.uri && message.diagnostics) {
                connection.sendDiagnostics({
                    uri: message.uri,
                    diagnostics: message.diagnostics
                });
                connection.console.log(`Diagnostics sent for ${message.uri}`);
            } else {
                connection.console.log(`Received message from compiler: ${messageStr}`);
            }
        } catch (err) {
            connection.console.error(`Failed to parse compiler output JSON: ${err}`);
        }
    }
});

// Handle compiler errors
compilerProcess.stderr?.on('data', (data: Buffer) => {
    connection.console.error(`Compiler stderr: ${data.toString()}`);
});

compilerProcess.on('error', (err) => {
    connection.console.error(`Compiler process error: ${err.message}`);
});

compilerProcess.on('exit', (code) => {
    connection.console.log(`Compiler process exited with code ${code}`);
});

// Optional: log all LSP notifications for debugging
connection.onNotification((method: string, params: any) => {
    connection.console.log(`Notification: ${method} - ${JSON.stringify(params)}`);
});

// Initialize handler
connection.onInitialize((params: InitializeParams): InitializeResult => {
    return {
        capabilities: {
            textDocumentSync: TextDocumentSyncKind.Incremental
        }
    };
});

// Cleanup
const disposables: Disposable[] = [];
process.on('exit', () => {
    compilerProcess.kill();
    disposables.forEach(d => d.dispose());
});

// Start listening
documents.listen(connection);
connection.listen();
