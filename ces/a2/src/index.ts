type Student = {
  name: string;
  grade: number;
  absences: number;
};

const numbers: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const students: Student[] = [
  { name: "Ana", grade: 9, absences: 2 },
  { name: "Mihai", grade: 7, absences: 5 },
  { name: "Ioana", grade: 10, absences: 1 },
  { name: "Vlad", grade: 6, absences: 7 },
  { name: "Radu", grade: 8, absences: 3 }
];

// 1) classic for -> map (squares of numbers)
const squaredNumbers = numbers.map((n) => n * n);

// 2) classic for -> filter (even numbers)
const evenNumbers = numbers.filter((n) => n % 2 === 0);

// 3) classic for -> reduce (sum of numbers)
const sumOfNumbers = numbers.reduce((acc, n) => acc + n, 0);

// 4) classic for -> map (extract student names)
const studentNames = students.map((student) => student.name);

// 5) classic for -> filter (students who passed, >= 8)
const passedStudents = students.filter((student) => student.grade >= 8);

// 6) classic for -> reduce (average grade)
const averageGrade =
  students.reduce((acc, student) => acc + student.grade, 0) / students.length;

console.log("1) map - squaredNumbers:", squaredNumbers);
console.log("2) filter - evenNumbers:", evenNumbers);
console.log("3) reduce - sumOfNumbers:", sumOfNumbers);
console.log("4) map - studentNames:", studentNames);
console.log(
  "5) filter - passedStudents:",
  passedStudents.map((student) => `${student.name} (${student.grade})`)
);
console.log("6) reduce - averageGrade:", averageGrade.toFixed(2));
