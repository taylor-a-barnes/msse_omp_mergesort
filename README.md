# Implementing Merge Sort With OpenMP

In `src/main.cpp`, you will find a code that initializes each rank with a random vector (named `sortvec`) of size `nvalues`.
It then performs a merge sort on the values in `sortvec`.

For this problem, you must parallelize the merge sort operation using OpenMP.
As we have discussed, merge sorts involve dividing a vector (or array or similar data structure) into smaller subvectors in a divide-and-conquer algorithm (note that "dividing" the data structure is usually just a matter of bookeeping - it is preferable to avoid creating new data structures for each new subdivision).
For the purpose of this problem, you should be able to have multiple threads simultaneously working to merge different subdivisions.
This is quite difficult to achieve late in the sorting process, when the total possible number of unsorted subdivisions becomes less than twice the number of threads.
For example, when the entire vector consists of two subdivisions, both of which are internally sorted, it is difficult for more than one thread to productively contribute to the merge.
For the purpose of grading this assignment, it is acceptable if some threads can't contribute to the final few subdivision merges - although I will note that there are a number of sophisticated strategies for parallelizing merge sorts that can avoid / mitigate this problem.

The code in `src/main.cpp` is a fairly typical representation of a merge sort, in the form of a recursive function.
Spend a bit of time thinking about how you would attempt to parallelize it using OpenMP.
Typically, this involves using somewhat more complex OpenMP concepts than we've covered in class (such as `sections` or `tasks`).
For the purpose of this problem, we will take a different approach.

Sometimes, algorithms may be expressible in very different forms that are nonetheless mathematically equivalent.
Although merge sort is traditionally expressed as a recursive algorithm, it is also quite straigthforward to perform non-recursive merge sorts.
A sensible strategy is as follows: start by dividing the entire vector into subdivisions of size `1`.
Merge all the size `1` subdivisions into subdivisions of size `2`.
Then merge the size `2` subdivisions into subdivisions of size `4`.
Repeat until you have sorted the entire vector.
You can do this in the form of two `for` loops.

Your task is as follows: refactor the code, so that the merge sort is performed non-recursively.
Then, parallelize the non-recursive merge sort operation using OpenMP.