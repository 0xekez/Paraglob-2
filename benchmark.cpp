#include <iostream>
#include <bits/stdc++.h>
#include <chrono>

#include "paraglob.h"

static const char* benchmark_pattern_words[] = {
    "aaaaaa", "bb", "cccccccccccccccc", "ddddd", "eeeeeeeee", "fffffffffffff", "gggg"
};

const char* random_pattern_word(){
    int idx = rand() % (sizeof(benchmark_pattern_words) / sizeof(const char*));
    return benchmark_pattern_words[idx];
}

const char* random_word()
{
    static char buffer[1024];

    int j;
    int rounds = (rand() % 25) + 5;
    for ( j = 0; j < rounds; j++ ) {
        buffer[j] = (char)((rand() % 26) + 'a');
    }

    buffer[rounds] = '\0';

    return buffer;
}

void benchmark(const char * a, const char * b, const char * c) {
  srand(time(0));
  long num_patterns = atol(a);
  long num_queries = atol(b);
  long match_prob = atol(c);

  std::cout << "creating workload \n";

  // Create the patterns.
  std::string patterns[num_patterns];
  char buffer[1024];
  int i, j;

  for ( i = 0; i < num_patterns; i++ ) {

      buffer[0] = '\0';

      int rounds = (rand() % 10) + 2;
      for ( j = 0; j < rounds; j++ ) {

          if ( j != 0 )
              strcat(buffer, "*");

          if ( (rand() % 10) == 0 ) {
              strcat(buffer, random_pattern_word());
            }
          else {
              strcat(buffer, random_word());
            }
      }

      std::string s(strdup(buffer));
      patterns[i] = s;
    }

    // Create the queries.

  std::string queries[num_queries];

  for ( i = 0; i < num_queries; i++ ) {

      buffer[0] = '\0';

      if ( (rand() % 100) <= match_prob ) {
          // Create a likely match candidate.
          int rounds = (rand() % 5) + 1;
          for ( j = 0; j < rounds; j++ ) {
              strcat(buffer, random_pattern_word());
          }
      }

      else {
          // Create a mismatch.
          int rounds = (rand() % 50) + 5;
          for ( j = 0; j < rounds; j++ ) {
              buffer[j] = (char)((rand() % 26) + 'a');
          }

          buffer[rounds] = '\0';
      }

      queries[i] = std::string(strdup(buffer));
  }

  std::cout << "creating paraglob \n";
  Paraglob myGlob;
  for (std::string p : patterns) {
    myGlob.add(p);
  }

  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "making queries \n";
  for (std::string q : queries) {
    myGlob.get(q);
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  std::cout << "Queries/second: " << num_queries/elapsed.count() << "\n";
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
      std::cout << "bad number of command line args \n";
      return -1;
    }
    benchmark(argv[1], argv[2], argv[3]);
    return 0;
}
