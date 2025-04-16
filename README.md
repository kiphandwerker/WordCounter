# Word counter
This is a simple function that reads in a text file and then creates a list of the number of occurences of each word. This function is not case sensitive and allows for the option to exclude words from the final output.

## 📚 Features

- Cleans words by removing punctuation and converting to lowercase
- Skips common stop words like "the", "and", "of", etc.
- Displays word frequencies in descending order
- Sorts alphabetically when frequencies match

## 🛠️ Usage
<ol>
<li>Place your text in a file named `example.txt` (or change the filename in `main()`).

<li>Compile the program:

```bash
g++ -std=c++11 -o word_counter word_counter.cpp
```

<li>Run the program

```bash
./word_counter
```
</ol>

## ✅ Requirements
- C++11 or later

- A text file named example.txt in the same directory

## 📌 Notes
- Only alphabetic characters are considered (punctuation is ignored).

- All words are converted to lowercase for accurate counting.

## 🧪 Future Upgrade Ideas

- Add n-grams (common phrases)
- GUI version
- Histogram