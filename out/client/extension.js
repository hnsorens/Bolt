"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || (function () {
    var ownKeys = function(o) {
        ownKeys = Object.getOwnPropertyNames || function (o) {
            var ar = [];
            for (var k in o) if (Object.prototype.hasOwnProperty.call(o, k)) ar[ar.length] = k;
            return ar;
        };
        return ownKeys(o);
    };
    return function (mod) {
        if (mod && mod.__esModule) return mod;
        var result = {};
        if (mod != null) for (var k = ownKeys(mod), i = 0; i < k.length; i++) if (k[i] !== "default") __createBinding(result, mod, k[i]);
        __setModuleDefault(result, mod);
        return result;
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.activate = activate;
exports.deactivate = deactivate;
const path = __importStar(require("path"));
const vscode = __importStar(require("vscode"));
const node_1 = require("vscode-languageclient/node");
let client;
async function activate(context) {
    const serverModule = context.asAbsolutePath(path.join('out', 'server', 'server.js'));
    console.log('Starting language server at:', serverModule);
    const serverOptions = {
        run: {
            command: 'node',
            args: [serverModule, '--stdio'],
            transport: node_1.TransportKind.stdio
        },
        debug: {
            command: 'node',
            args: [
                '--inspect=6009',
                serverModule,
                '--stdio'
            ],
            transport: node_1.TransportKind.stdio
        }
    };
    const clientOptions = {
        documentSelector: [{ scheme: 'file', language: 'bolt' }],
        outputChannel: vscode.window.createOutputChannel('Bolt Output')
    };
    client = new node_1.LanguageClient('boltLanguageServer', 'Bolt Language Server', serverOptions, clientOptions);
    try {
        // Proper async startup with error handling
        await client.start();
        console.log('Language client started successfully');
    }
    catch (err) {
        console.error('Failed to start language server:', err);
        vscode.window.showErrorMessage(`Bolt extension failed to start: ${err instanceof Error ? err.message : String(err)}`);
    }
}
function deactivate() {
    return client?.stop();
}
//# sourceMappingURL=extension.js.map