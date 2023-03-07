# word_stat
Simple Text Statistics.

Calculate the most frequently occurring words, the number of unique words and the number of vowels.


---


# Example

```bash
./word_stat -s "Outside of Japan, it was re-badged as the 200SX and in the US market as the Nissan 240SX, paired with the single overhead cam KA24E motor and later with the dual-overhead model KA24DE."
```

```
1. the (5)
2. as (2)
3. and (2)
4. with (2)
5. later (1)
6. market (1)
7. overhead (1)
8. cam (1)
9. model (1)
10. 240sx (1)

Number of unique words: 26.
Total number of words: 33.
Unique-to-total word ratio: 78.79%.

Number of vowels: 55.
Total number of consonants: 82.
Vowel-to-consonant ratio: 67.07%.
```


---


# Setup

### 1. Generate Makefile.

```bash
mkdir build && cd build
cmake ..
```

### 2. Compile.

```bash
make
```


Alternatively, compile using all cores (MacOS):

```bash
make -j `sysctl -n hw.ncpu`
```


### 3. Run.

```bash
./word_stat
```


---


# Commands

### 1. Get help.

```bash
./word_stat -h
```

```
usage: ./word_stat [-h | --help] [-f <filename>] [-s <string>]

options:
  -h | --help                 print this help message
  -f <filename>               filename to be processed (default: "file.txt")
  -s <filename>               string to be processed
```

### 2. Process a txt file.

`./word_stat -f "FILEPATH.TXT"`

```bash
./word_stat -f "mazda.txt"
```

```
1. a (12)
2. the (10)
3. as (7)
4. of (6)
5. was (5)
6. rx7 (4)
7. in (4)
8. rotary (4)
9. engine (4)
10. offered (3)

Number of unique words: 85.
Total number of words: 153.
Unique-to-total word ratio: 55.56%.

Number of vowels: 271.
Total number of consonants: 426.
Vowel-to-consonant ratio: 63.62%.
```

### 3. Process a raw string.

`./word_stat -s "STRING"`

```bash
./word_stat -s "After a 16-year hiatus, the GT-R name was revived in 1989 as the BNR32 Skyline GT-R. Group A specification versions of the R32 GT-R were used to win the Japanese Touring Car Championship for four years in a row."
```

```
1. the (4)
2. gtr (3)
3. a (3)
4. in (2)
5. japanese (1)
6. were (1)
7. of (1)
8. group (1)
9. win (1)
10. versions (1)

Number of unique words: 31.
Total number of words: 39.
Unique-to-total word ratio: 79.49%.

Number of vowels: 61.
Total number of consonants: 95.
Vowel-to-consonant ratio: 64.21%.
```
