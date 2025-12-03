const express = require("express");
const app = express();

// Middleware
app.use(express.json());

// CORS
app.use((req, res, next) => {
  res.header("Access-Control-Allow-Origin", "*");
  res.header(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  res.header("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
  if (req.method === "OPTIONS") return res.sendStatus(200);
  next();
});

// In-memory "database" on server
let employees = [];

// GET /employees
app.get("/employees", (req, res) => {
  res.json(employees);
});

// POST /employees
app.post("/employees", (req, res) => {
  const e = req.body;

  // basic calculation like your C code
  const salary = Number(e.emp_salary) || 0;
  const wd = Number(e.emp_working_days) || 0;
  const bonus = Number(e.emp_bonus) || 0;
  const ded = Number(e.emp_deductions) || 0;
  const wages = salary / 26.0;
  const net = wages * wd + bonus - ded;

  const emp = {
    emp_id: e.emp_id,
    emp_name: e.emp_name,
    emp_dept: e.emp_dept,
    emp_email: e.emp_email,
    emp_phone: e.emp_phone,
    emp_address: e.emp_address || "",
    emp_payroll_id: e.emp_payroll_id,
    emp_salary: salary,
    emp_working_days: wd,
    emp_leaves: Number(e.emp_leaves) || 0,
    emp_bonus: bonus,
    emp_deductions: ded,
    emp_net_pay: net,
    emp_status: e.emp_status || "Active"
  };

  employees.push(emp);
  res.json({ message: "OK", emp });
});

// Use Render's PORT or 3000 locally
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
