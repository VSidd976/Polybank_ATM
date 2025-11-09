import type { Card } from "@components/BankCard/consts";
import { create } from "zustand";

type CardStore = {
  card: Card | undefined;
  updateCard: (c: Card) => void;
};

const CARD_CREDS_KEY = "card-credentials";

function getFromLs(): Card | undefined {
  try {
    return JSON.parse(localStorage.getItem(CARD_CREDS_KEY) ?? "") as Card;
  } catch {
    return undefined;
  }
}

function writeToLs(card: Card): void {
  try {
    localStorage.setItem(CARD_CREDS_KEY, JSON.stringify(card));
  } catch {
    // error
  }
}

export const useCard = create<CardStore>((set) => ({
  card: getFromLs(),
  updateCard: (card) => {
    writeToLs(card);
    set({ card });
  },
}));
