#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void print_result(int * wins, size_t n_hands, int trails) {
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, wins[i], trails, (double) wins[i] * 100 / (double) trails);
  }
  printf("And there were %u ties\n", wins[n_hands]);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: test <input_file_name> <trials_num>\n");
    return EXIT_FAILURE;
  }

  int num_trails = 10000;
  if (argc > 2 && atoi(argv[2]) > 0) {
    num_trails = atoi(argv[2]);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open input file '%s'.\n", argv[1]);
    return EXIT_FAILURE;
  }

  size_t n_hands = 0;

  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;

  deck_t ** hands = read_input(f, &n_hands, fc);
  deck_t * remaining = build_remaining_deck(hands, n_hands);

  int wins[n_hands+1];

  for (int i = 0; i < n_hands+1; i++) {
    wins[i] = 0;
  }

  // Monte Carlo trial
  for (size_t i = 0; i < num_trails; i++) {
    shuffle(remaining);
    future_cards_from_deck(remaining, fc);

    int maxidx = 0;
    int tieidx = 0;
    for (int j = 1; j < n_hands; j++) {
      int result = compare_hands(hands[maxidx], hands[j]);
      if (result == 0) {
	tieidx = j;
      }
      if (result < 0) {
	maxidx = j;
	tieidx = j;
      }
    }
    if (maxidx == tieidx) {
      wins[maxidx]++;
    } else {
      wins[n_hands]++;
    }
  }

  print_result(wins, n_hands, num_trails);

  if (fclose(f) == EOF) {
    fprintf(stderr, "Failed to close input file '%s'.\n", argv[1]);
    return EXIT_FAILURE;
  }

  free_deck(remaining);

  for (int i = 0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);

  for (int i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  return EXIT_SUCCESS;
}
