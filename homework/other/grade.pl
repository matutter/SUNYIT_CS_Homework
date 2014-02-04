#!/usr/bin/perl

## Turns off buffering
$| = 1;

print "Content-type: text/html\n\n";

open(GRADES, "grades") || die "Can't open grades: $!\n";
#open(GRADES, "grades") || { $openfailed = TRUE };
#if ($openfailed) {
	#print("openfailed\n");
	#exit;
#}
while ($line = <GRADES>) {
    ($student, $grade) = split(/ /, $line);
    chop $grade;
print "STUDENT $student GRADE $grade \n";
    $grades{$student} .= $grade . " ";
}

foreach $student (sort keys %grades) {
    $scores = 0;
    $total = 0;    
    @grades = split(/ /, $grades{$student});
print "GRADE ARRAY SIZE $#grades  \n";
print "GRADE ARRAY $grades[0] $grades[1] \n";
    foreach $grade (@grades) {
        $total += $grade;
        $scores++;
    }
    $average = $total / $scores;
    print "$student: $grades{$student}\tAverage: $average\n";
}
# GRADE ARRAY SIZE 3  
# GRADE ARRAY 1 3 
# scott: 1 3 4 2  Average: 2.5
$j=0;
$i=0;
while($j <9) {
 $j=$j+1;
 $i=$i+$j;
}
print "I is: $i\n";

