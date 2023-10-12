#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  // fprintf(stderr, "%c %c ", value_letter(c), suit_letter(c));
  assert(c.value >= 2);
  assert(c.value <= VALUE_ACE);
  assert(c.suit != NUM_SUITS);
}

const char * ranking_to_string(hand_ranking_t r) {

  char * desc = "";
  switch(r) {
    case STRAIGHT_FLUSH:
      desc = "STRAIGHT_FLUSH";
      break;
    case FOUR_OF_A_KIND:
      desc = "FOUR_OF_A_KIND";
      break;
    case FULL_HOUSE:
      desc = "FULL_HOUSE";
      break;
    case FLUSH:
      desc = "FLUSH";
      break;
    case STRAIGHT:
      desc = "STRAIGHT";
      break;
    case THREE_OF_A_KIND:
      desc = "THREE_OF_A_KIND";
      break;
    case TWO_PAIR:
      desc = "TWO_PAIR";
      break;
    case PAIR:
      desc = "PAIR";
      break;
    case NOTHING:
      desc = "NOTHING";
      break;
  }
  char const* p = desc;
  return p;
}

char value_letter(card_t c) {
  if (c.value <= 10) {
    return '0' + c.value % 10;
  }
  switch(c.value) {
  case VALUE_ACE:
    return 'A';
  case VALUE_KING:
    return 'K';
  case VALUE_QUEEN:
    return 'Q';
  case VALUE_JACK:
    return 'J';
  }
  return 'x';
}


char suit_letter(card_t c) {
  switch(c.suit) {
  case SPADES:
    return 's';
  case HEARTS:
    return 'h';
  case DIAMONDS:
    return 'd';
  case CLUBS:
    return 'c';
  case NUM_SUITS:
    return ' ';
  }
  return 'x';
  
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let == '0') {
    temp.value = 10;
  } else if (value_let <= '9') {
    temp.value = value_let - '0';
  } else if (value_let == 'A') {
    temp.value = VALUE_ACE;
  } else if (value_let == 'K') {
    temp.value = VALUE_KING;
  } else if (value_let == 'Q') {
    temp.value = VALUE_QUEEN;
  } else if (value_let == 'J') {
    temp.value = VALUE_JACK;
  }

  if (suit_let == 's') {
    temp.suit = SPADES;
  } else if (suit_let == 'h') {
    temp.suit = HEARTS;
  } else if (suit_let == 'd') {
    temp.suit = DIAMONDS;
  } else if (suit_let == 'c') {
    temp.suit = CLUBS;
  }

  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = 0;
  temp.suit = NUM_SUITS;

  temp.value = c % 13 + 2;
  temp.suit = SPADES + c / 13;
  
  assert_card_valid(temp);
  return temp;
}
