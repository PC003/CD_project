const express = require('express');
const cors = require('cors');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');
const os = require('os');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

app.post('/api/optimize', (req, res) => {
    const { rule, expression } = req.body;
    
    if (!rule) {
        return res.status(400).json({ error: "Rule is required" });
    }

    const tempFileName = path.join(os.tmpdir(), `rule_${Date.now()}.nlopt`);
    
    fs.writeFile(tempFileName, rule, (err) => {
        if (err) return res.status(500).json({ error: "Failed to write rule file" });

        // Pipe expression to nlopt if provided, or just send exit
        const inputExpr = expression ? expression + "\nexit\n" : "exit\n";
        
        // Execute the binary
        const nloptPath = path.resolve(__dirname, '../build/nlopt');
        const command = `echo "${inputExpr}" | ${nloptPath} ${tempFileName}`;
        
        exec(command, (execErr, stdout, stderr) => {
            // Clean up temp file
            fs.unlink(tempFileName, () => {});
            
            if (execErr && !stdout) {
                return res.status(500).json({ error: stderr || execErr.message });
            }
            
            res.json({
                output: stdout,
                error: stderr
            });
        });
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Frontend running on http://localhost:${PORT}`);
});
