#include <stdio.h>
#include <stdlib.h>

#include "cards.h"
#include "deck.h"
#include "eval.h"

int main(void) {
  deck_t * deck = malloc(sizeof(*deck));
  card_t c = card_from_letters('0', 's');
  add_card_to(deck, c);
  free_deck(deck);
  return EXIT_SUCCESS;
}
