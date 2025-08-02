async function fetchGPTResponse() {
  const apiKey = "YOUR_API_KEY";
  const response = await fetch("https://api.openai.com/v1/chat/completions", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
      "Authorization": `Bearer ${apiKey}`
    },
    body: JSON.stringify({
      model: "gpt-4.1",
      messages: [{ role: "user", content: "Whats 1+1, in one word." }]
    })
  });
  const data = await response.json();
  return data.choices[0].message.content;
}

let gpt_callback_ptr = 0;  // fix: use let or var, not "function"

function callGPT(callbackPtr) {
  gpt_callback_ptr = callbackPtr;
  fetchGPTResponse().then((result) => {
    const lengthBytes = lengthBytesUTF8(result) + 1;
    const stringOnWasmHeap = _malloc(lengthBytes);
    stringToUTF8(result, stringOnWasmHeap, lengthBytes);
    // Call C++ callback with pointer to string
    Module.ccall('onGPTResponse', 'void', ['number'], [stringOnWasmHeap]);
  });
}

