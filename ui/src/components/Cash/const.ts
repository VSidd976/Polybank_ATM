import one from "@assets/money/1_money.jpeg";
import two from "@assets/money/2_money.jpeg";
import five from "@assets/money/5_money.jpg";
import ten from "@assets/money/10_money.jpeg";
import hundred from "@assets/money/100_money.jpeg";

export const CASH_NOMINALS: Record<number, string> = {
  1: one,
  2: two,
  5: five,
  10: ten,
  100: hundred,
} as const;

export type Nominal = keyof typeof CASH_NOMINALS;
