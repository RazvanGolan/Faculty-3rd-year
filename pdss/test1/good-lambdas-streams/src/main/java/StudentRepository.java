import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class StudentRepository {
    private Collection<Student> students;

    public StudentRepository(Collection<Student> students) {
        this.students = new ArrayList<>(students);
    }

    public List<String> getStudentEmailsSortedByAgeUnderTheAgeOf(int age) {
        return students.stream()
                .filter(s->s.getAge() < age)
                .sorted(Comparator.comparingInt(Student::getAge))
                .map(Student::getEmail)
                .collect(Collectors.toList());
    }

    /**
     * @return returns the sorted list of distinct names.
     *
     * SIDE EFFECT: makes all student names uppercase
     */
    public List<String> makeStudentNamesUppercaseAndReturnThemAsSortedDistinctList() {
        return students.stream()
                .peek(s -> s.setName(s.getName().toUpperCase()))
                .map(Student::getName)
                .distinct()
                .sorted()
                .collect(Collectors.toList());
    }

    public Set<String> getNonNullUniversities() {
        return students.stream()
                .map(Student::getUniversity)
                .filter(Objects::nonNull)
                .collect(Collectors.toSet());
    }

    public Map<String, Student> getStudentsMappedByEmail() {
        return students.stream()
                .collect(Collectors.toMap(Student::getEmail, Function.identity()));
    }

    public Map<String, List<Student>> getOverageStudentsGroupedByUniversity() {
        return students.stream()
                .filter(Student::isOverage)
                .filter(student -> student.getUniversity() != null)
                .collect(Collectors.groupingBy(Student::getUniversity));
    }

    public Optional<Student> getTheStudentWithTheNthShortestEmail(int n) {
        return students.stream()
                .sorted(Comparator.comparingInt(student->student.getEmail().length()))
                .skip(n-1)
                .findFirst();
    }

    public Optional<String> getTheNameOfTheSecondOldestStudent() {
        return students.stream()
                .sorted(Comparator.comparingInt(Student::getAge).reversed())
                .skip(1)
                .findFirst()
                .map(Student::getName);
    }

    public OptionalDouble getAverageAgeOfNStudentsInUniversity(int n, String university) {
        return students.stream()
                .filter(student -> student.getUniversity() != null)
                .filter(student -> student.getUniversity().equals(university))
                .limit(n)
                .mapToInt(Student::getAge)// only works with mapToInt
                .average();
    }

    public long countStudentsWithNamesLongerThan(int n) {
        return students.stream()
                .filter(student -> student.getName().length() > n)
                .count();
    }

    // Students in no university (university == null) are considered to be in the same university
    public double countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n) {
        return students.stream()
                .filter(student -> student.getColleagues().stream()
                        .map(Student::getUniversity)
                        .filter(univ-> {
                            if(univ == null)
                                return student.getUniversity() != null;
                            return !univ.equals(student.getUniversity());
                        })
                        .count() >= n
                )
                .count();
    }

    public List<Student> getStudentsWithAtLeastOneColleagueWithDifferentEmailDomain() {
        return students.stream()
                .filter(student -> student.getColleagues().stream()
                        .map(Student::getEmail)
                        .map(StudentRepository::getEmailDomain)
                        .anyMatch(domain -> getEmailDomain(student.getEmail()).equals(domain)))
                .collect(Collectors.toList());
    }

    private static String getEmailDomain(String email) {
        if(email.indexOf('@') == -1) {
            return "";
        }
        return email.substring(email.indexOf('@') + 1);
    }
}
