#!/usr/bin/env node
const readline = require('readline')
const k = require('./napi/module.js').k

console.log('kc')

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: true,
    prompt: ' '
});

rl.prompt(true);

rl.on('line', (line) => {
    if (line.trim() === '\\\\')
        rl.close();
    try {
        console.log(k(line));
    } catch (e) {
        console.error('error: ', e.message);
    }
    rl.prompt(true);
}).on('close', () => {
    process.exit(0);
}).on('error', err => console.log(err));
