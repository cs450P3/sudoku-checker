gcc sudoku.c -o sudoku.x -lpthread

echo ""
echo "valid test"


./sudoku.x < input_file.txt

echo ""
echo "invalid test 1"


./sudoku.x < input_file_2.txt
echo ""
echo "invalid test 2"


./sudoku.x < input_file_20.txt
