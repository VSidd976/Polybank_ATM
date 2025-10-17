import PolyBank from "@assets/logo.svg";
import Visa from "@assets/Visa.svg";

export const BANKS = {
  POLY_BANK: "PolyBank",
} as const;

export const TRANSACTION_COMPANY = {
  VISA: "VISA",
  MASTER_CARD: "MASTER_CARD",
} as const;

export type Card = {
  ownerName: string;
  cvv: string;
  expDate: string;
  number: string;
  bank: Bank;
  transactionCompany: TransactionCompany;
};

export type Bank = (typeof BANKS)[keyof typeof BANKS];
export type TransactionCompany =
  (typeof TRANSACTION_COMPANY)[keyof typeof TRANSACTION_COMPANY];

export const BANK_LOGOS: Record<Bank, string> = {
  [BANKS.POLY_BANK]: PolyBank,
} as const;

export const COMPANY_LOGO: Record<TransactionCompany, string> = {
  [TRANSACTION_COMPANY.VISA]: Visa,
  [TRANSACTION_COMPANY.MASTER_CARD]: Visa, // maybe add logo later if have time
} as const;
