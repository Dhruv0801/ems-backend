const express = require("express");
const { execFile } = require("child_process");
const path = require("path");
const app = express();

app.use(express.json());

// Simple permissive CORS for local development
app.use((req, res, next) => {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  if (req.method === "OPTIONS") return res.sendStatus(200);
  next();
});

app.get("/employees", (req, res) => {
  const exe = path.join(__dirname, "..", process.platform === "win32" ? "employee.exe" : "employee");
  execFile(exe, ["list"], (err, stdout, stderr) => {
    if (err) return res.status(500).json({ error: stderr || err.message });
    res.type("json").send(stdout);
  });
});

app.post("/employees", (req, res) => {
  const e = req.body;
  const exe = path.join(__dirname, "..", process.platform === "win32" ? "employee.exe" : "employee");
  execFile(
    exe,
    [
      "add",
      e.emp_id,
      e.emp_name,
      e.emp_dept,
      e.emp_email,
      e.emp_phone,
      e.emp_payroll_id,
      String(e.emp_salary),
      String(e.emp_working_days),
      String(e.emp_leaves),
      String(e.emp_bonus),
      String(e.emp_deductions),
      e.emp_address || "",
      e.emp_status || "Active"
    ],
    (err, stdout, stderr) => {
      if (err) return res.status(500).json({ error: stderr || err.message });
      res.json({ message: "OK", output: stdout });
    }
  );
});

app.listen(3000, () => console.log("Server on http://localhost:3000"));
