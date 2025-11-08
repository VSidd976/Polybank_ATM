import {
  BANKS,
  TRANSACTION_COMPANY,
  type Card,
} from "@components/BankCard/consts";
import { randomInRange } from "@utils/randomInRange";
import { useCallback, useState } from "react";

const defaultFields: Pick<Card, "bank" | "transactionCompany"> = {
  bank: BANKS.POLY_BANK,
  transactionCompany: TRANSACTION_COMPANY.VISA,
} as const;

const OWNERS = [
  "Alexandr Stepanov",
  "Alex Smith",
  "Jordan Brown",
  "Taylor Johnson",
  "Morgan Davis",
  "Sam Miller",
  "Casey Wilson",
  "Jamie Clark",
  "Riley Lewis",
  "Avery Thompson",
  "Dylan Moore",
  "Logan White",
  "Cameron Hall",
  "Peyton Allen",
  "Quinn Young",
  "Hayden King",
  "Reese Wright",
  "Rowan Scott",
  "Blake Green",
  "Charlie Adams",
  "Emerson Baker",
];

function generateCard(): Card {
  return {
    ...defaultFields,
    number: `${randomInRange(4556_0000_0000_0000, 4556_9999_9999_9999)}`,
    expDate: `${randomInRange(1, 12).toString().padStart(2, "0")}/${randomInRange(25, 35).toString().padStart(2, "0")}`,
    ownerName: OWNERS[randomInRange(0, OWNERS.length - 1)],
    cvv: randomInRange(0, 999).toString().padStart(3, "0"),
  };
}

export const useRandomCard = (initialCard?: Card) => {
  const [card, setCard] = useState(initialCard ?? generateCard());
  const generateNew = useCallback(() => setCard(generateCard), [setCard]);
  return [card, generateNew] as const;
};
