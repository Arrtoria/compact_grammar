This is my optimized code.

!!I have optimized everything!!

The first and most important thing I accomplished was picking the right data structure which made me extra comfortable throughout the coding process!

The second optimization is actually error correction.

In addition, I realized that the relationship between parents and children cannot be realized by a single-dimensional parent or child array. So I used a two-dimensional array to ensure correctness.
Of course, the code is a little more complicated, but the naming should be relatively clear and easy to read.

I asked chatgpt to write a simple comment on my code for your reference.

```markdown
/*
 * This program reads a grammar from a file, builds a tree structure to mark reachable and unreachable parts,
 * and then compacts the grammar based on the tree structure. The resulting grammar is printed for verification.
 *
 * Functions:
 * - print_table(): Prints the content of the grammar table.
 * - find_ancestors(): Finds ancestors of a given character in the grammar tree.
 * - find_children(): Finds children of a given character in the grammar tree.
 * - read_grammar_from_file(): Reads the grammar from a file and populates the grammar table.
 * - build_tree(): Builds the tree structure based on the grammar.
 * - compact_grammar(): Compacts the grammar based on the tree structure, marking reachable and unreachable parts.
 *
 * Data Structures:
 * - table: 3-dimensional array to store grammar rules.
 * - exist: Array to store existing characters in the grammar.
 * - parent: 2-dimensional array to store parent relationships in the grammar tree.
 * - child: 2-dimensional array to store child relationships in the grammar tree.
 * - cnt: Counter for the number of characters in the grammar.
 * - start: Start symbol of the grammar.
 * - ok: Array to mark characters that can reach the terminator.
 * - notok: Array to mark characters that cannot reach the terminator.
 */

The method of use is to enter ./runsh in the shell
You can modify input.txt to see if you can achieve your expected results

Input format:
Please do not use something like
S->A
S->B
Instead,You should use something like
S->A|B

Only supports Context Free Grammar.

