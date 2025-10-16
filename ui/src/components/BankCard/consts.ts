export const BANKS = {
    POLY_BANK: "PolyBank",
} as const;

export const TRANSACTION_COMPANY = {
    VISA: "VISA",
    MASTER_CARD: "MASTER_CARD",
} as const;

export type Bank = (typeof BANKS)[keyof typeof BANKS];
export type TransactionCompany =
    (typeof TRANSACTION_COMPANY)[keyof typeof TRANSACTION_COMPANY];
