document.addEventListener('DOMContentLoaded', () => {
    const optimizeBtn = document.getElementById('optimizeBtn');
    const ruleInput = document.getElementById('ruleInput');
    const expressionInput = document.getElementById('expressionInput');
    const terminalOutput = document.getElementById('terminalOutput');

    function formatTerminalOutput(text) {
        // Simple highlighting for typical compiler output
        return text
            .replace(/Status: SUCCESS/g, '<span class="success-text">Status: SUCCESS</span>')
            .replace(/✓ /g, '<span class="success-text">✓ </span>')
            .replace(/✗ /g, '<span class="error-text">✗ </span>')
            .replace(/(Before optimization:|After optimization:)/g, '<span class="highlight-text">$1</span>')
            .replace(/MATCH: rule applied/g, '<span style="color: #e5c07b;">MATCH: rule applied</span>')
            .replace(/Error:/g, '<span class="error-text">Error:</span>')
            .replace(/Parse Error:/g, '<span class="error-text">Parse Error:</span>')
            .replace(/SEMANTIC ERROR:/g, '<span class="error-text">SEMANTIC ERROR:</span>')
            .replace(/Syntax Error:/g, '<span class="error-text">Syntax Error:</span>');
    }

    optimizeBtn.addEventListener('click', async () => {
        const rule = ruleInput.value.trim();
        const expression = expressionInput.value.trim();

        if (!rule) {
            terminalOutput.innerHTML = '<span class="error-text">Error: Optimization rule cannot be empty.</span>';
            return;
        }

        optimizeBtn.textContent = 'Compiling...';
        optimizeBtn.disabled = true;
        
        terminalOutput.innerHTML = '<i>Processing compilation pipeline...</i>';

        try {
            const response = await fetch('/api/optimize', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ rule, expression })
            });

            const data = await response.json();

            if (response.ok) {
                // If there's stdout, show it, else show stderr if error occurred in exec
                let out = data.output || data.error || 'No output received.';
                terminalOutput.innerHTML = formatTerminalOutput(out);
            } else {
                terminalOutput.innerHTML = `<span class="error-text">Server Error: ${data.error || 'Unknown error occurred'}</span>`;
            }
        } catch (err) {
            terminalOutput.innerHTML = `<span class="error-text">Network Error: ${err.message}</span>`;
        } finally {
            optimizeBtn.textContent = 'Compile & Optimize';
            optimizeBtn.disabled = false;
        }
    });
});
