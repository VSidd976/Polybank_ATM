import type { ReactElement } from "react";
import type { Bank, TransactionCompany } from "./consts";

type Props = {
  ownerName: string;
  cvv: number;
  expDate: string;
  number: string;
  bank: Bank;
  transactionCompany: TransactionCompany;
};

const BankCard = ({
  ownerName,
  cvv,
  expDate,
  number,
  bank,
}: Props): ReactElement => {
  return <div> </div>;
};

export default BankCard;
