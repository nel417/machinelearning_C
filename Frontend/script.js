import Module from './neural.js';

Module().then((wasm) => {
    console.log("WebAssembly Loaded!");

    // Wrap C functions
    const trainNetwork = wasm.cwrap('train_network', 'void', ['number', 'number', 'number', 'number']);
    const costFunction = wasm.cwrap('cost', 'number', ['number']);

    // Allocate memory for the neural network struct
    const nnSize = 3 * 4; // 3 floats * 4 bytes each
    const nnPtr = wasm._malloc(nnSize);
    const view = new Float32Array(wasm.HEAPF32.buffer, nnPtr, 3);

    // Initialize weights randomly
    view[0] = Math.random();
    view[1] = Math.random();
    view[2] = Math.random();

    document.getElementById('train-btn').addEventListener('click', () => {
        // Get user input values
        const iterations = parseInt(document.getElementById('iterations').value, 10);
        const epsilon = parseFloat(document.getElementById('epsilon').value);
        const learningRate = parseFloat(document.getElementById('learning-rate').value);

        // Train the network with user-defined parameters
        trainNetwork(nnPtr, iterations, epsilon, learningRate);

        // Get the updated cost and weights
        const newCost = costFunction(nnPtr);
        const weight1 = view[0];
        const weight2 = view[1];
        const bias = view[2];

        // Display results
        document.getElementById('output').innerText = 
            `cost = ${newCost.toFixed(5)}, weight1 = ${weight1.toFixed(5)}, weight2 = ${weight2.toFixed(5)}, bias = ${bias.toFixed(5)}`;
    });
});
