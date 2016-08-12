#!/usr/local/bin/fish

# Expected to be inside testInput
set testDir testInput
set files $argv
set failures

#run tests
for file in $files

	set original $testDir/$file
	set compressed $file.compressed
	set uncompressed $file.uncompressed

	# a faulure is i defference in the orginal and uncompressed versions
	./compress $original $compressed
	./uncompress $compressed $uncompressed
	diff $original $uncompressed > /dev/null

	# collect failures
	if test $status -ne 0
		set failures $failures $file
	end

end

# print failures
if test (count $failures) -ne 0
	echo "Failed on:"
	for failure in $failures
		echo \t$failure
	end
end

