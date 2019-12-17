# Simple NAT

This is my simplified NAT program created for the Coding Challenge for the System Software Engineering Intern, VEN, Summer 2020 Position

## Compiling

If using a Linux-based system, simply type ``` make ``` into terminal. 

If unable to use ``` make ```, type ``` g++ -g -Wall -std=c++11 main.cpp -o simp_nat ```

If compiliation is successful, run program by typing ``` ./simp_nat ```

## Testing

I tested my solution with the sample inputs provided in the email as well as several other cases as provided by the test input files in this repository. If given more time, I would have tested for even more extreme test cases.

## Performance

Given the time-frame, I know that my solution may be on the slower end because of the nested for-loop. I am aware that my solution may have a worst case of O(n^2). If I had more time to work on the program, I would try to find a solution that would avoid the nested for-loop so that the time-complexity could be even lower (maybe something like O(n)). 

## Authors

* **Jason Chan** - [harharjason](https://github.com/harharjason)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


