const express = require("express");
const mongoose = require("mongoose");
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

// 1) CONNECT TO MONGODB ATLAS
const MONGO_URI =
  "mongodb+srv://Dhruv0801_db_user:Dhruv%407827@cluster0.dr1brz0.mongodb.net/emsdb?retryWrites=true&w=majority";

mongoose
  .connect(MONGO_URI)
  .then(() => console.log("MongoDB connected"))
  .catch(err => console.error("Mongo error:", err));

// 2) DEFINE EMPLOYEE MODEL
const employeeSchema = new mongoose.Schema({
  emp_id: { type: String, required: true, unique: true },
  emp_name: String,
  emp_dept: String,
  emp_email: String,
  emp_phone: String,
  emp_address: String,
  emp_payroll_id: String,
  emp_salary: Number,
  emp_working_days: Number,
  emp_leaves: Number,
  emp_net_pay: Number,
  emp_bonus: Number,
  emp_deductions: Number,
  emp_status: String
});

const Employee = mongoose.model("Employee", employeeSchema);

// 3) ROUTES

// GET /employees
app.get("/employees", async (req, res) => {
  try {
    const employees = await Employee.find().lean();
    res.json(employees);
  } catch (err) {
    console.error("GET /employees error:", err);
    res.status(500).json({ error: "Server error" });
  }
});

// POST /employees
app.post("/employees", async (req, res) => {
  try {
    const e = req.body;

    const salary = Number(e.emp_salary) || 0;
    const wd = Number(e.emp_working_days) || 0;
    const bonus = Number(e.emp_bonus) || 0;
    const ded = Number(e.emp_deductions) || 0;
    const wages = salary / 26.0;
    const net = wages * wd + bonus - ded;

    const emp = new Employee({
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
    });

    await emp.save();
    res.json({ message: "OK", emp });
  } catch (err) {
    console.error("POST /employees error:", err);
    res.status(500).json({ error: "Server error" });
  }
});

// root route
app.get("/", (req, res) => {
  res.send("EMS backend with MongoDB is running");
});

// PORT for Render or local
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log("Server running on port", PORT);
});
