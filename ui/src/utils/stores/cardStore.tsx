import type { Card } from "@components/BankCard/consts";
import { create } from "zustand";

type CardStore = {
  card: Card | undefined;
  updateCard: (c: Card) => void;
};

export const useCard = create<CardStore>((set) => ({
  card: undefined,
  updateCard: (card) => set({ card }),
}));
