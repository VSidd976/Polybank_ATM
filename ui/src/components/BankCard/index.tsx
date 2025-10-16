import { forwardRef, type ForwardedRef, type ReactElement } from "react";
import {
  BANK_LOGOS,
  COMPANY_LOGO,
  type Bank,
  type TransactionCompany,
} from "./consts";
import { styled } from "@mui/material";
import { useMemoValue } from "../../utils/hooks/useMemoValue";
import { formatCardNumber } from "../../utils/format";

type Props = {
  ownerName: string;
  cvv: number;
  expDate: string;
  number: string;
  bank: Bank;
  transactionCompany: TransactionCompany;
  className?: string;
};

const BankCard = (
  { number, transactionCompany, bank, className, ...footerInfo }: Props,
  ref: ForwardedRef<HTMLDivElement>,
): ReactElement => {
  return (
    <Container className={className} ref={ref}>
      <CardHeader bank={bank} transactionCompany={transactionCompany} />
      <CardNumber number={number} />
      <CardFooter {...footerInfo} />
    </Container>
  );
};

export default forwardRef(BankCard);

const CardHeader = ({
  bank,
  transactionCompany,
}: Pick<Props, "bank" | "transactionCompany">): ReactElement => {
  const logoSrc = useMemoValue((b) => BANK_LOGOS[b], [bank]);
  const companySrc = useMemoValue((t) => COMPANY_LOGO[t], [transactionCompany]);
  return (
    <HeaderWrapper>
      <img src={logoSrc} width={142} />
      <img src={companySrc} width={86} />
    </HeaderWrapper>
  );
};

const Container = styled("div")`
  display: flex;
  transition: all 0.3s ease;
  flex-direction: column;
  gap: 17.25px;
  height: 230px;
  width: 370px;
  padding: 25px 22px;
  box-shadow: 4px 4px 4px 0px #00000040;
  background: linear-gradient(
    120.68deg,
    #00dbc4 -14.5%,
    #01b2ac 37.63%,
    #02707e 95.04%
  );
  border-radius: 20px;
`;

const HeaderWrapper = styled("div")`
  display: flex;
  width: 100%;
  justify-content: space-between;
`;

const CardNumber = ({ number }: Pick<Props, "number">): ReactElement => {
  const formatedNumber = useMemoValue(formatCardNumber, [number]);
  return (
    <CardNumberWrapper>
      <MagneticRectangle />
      <Number>{formatedNumber}</Number>
    </CardNumberWrapper>
  );
};

const CardNumberWrapper = styled("div")`
  flex: 1;
  color: #1a3d3e;
  font-weight: 600;
`;

const MagneticRectangle = styled("div")`
  background: linear-gradient(116.79deg, #fffcfb 0%, #9effec 103.25%);
  width: 48.6px;
  height: 33.25px;
  border-radius: 6px;
`;

const Number = styled("span")`
  display: inline-block;
  font-size: 20px;
  margin-top: 5px;
`;

const CardFooter = ({
  ownerName,
  expDate,
  cvv,
}: Pick<Props, "cvv" | "ownerName" | "expDate">): ReactElement => {
  return (
    <CardFooterWrapper>
      <FooterItem label="Owner Name">{ownerName}</FooterItem>
      <FooterItem label="Expiration Date">{expDate}</FooterItem>
      <FooterItem label="CVV">{`${cvv}`}</FooterItem>
    </CardFooterWrapper>
  );
};

const MAX_LENGTH = 25;

const FooterItem = ({
  label,
  children,
}: {
  label: string;
  children: string;
}): ReactElement => {
  return (
    <Item>
      <label>{label}</label>
      <p>{children.slice(0, MAX_LENGTH)}</p>
    </Item>
  );
};

const CardFooterWrapper = styled("div")`
  display: flex;
  gap: 20.5px;
  color: #fffcfb;
`;

const Item = styled("div")`
  & > label {
    font-size: 10px;
    font-weight: 500;
  }
  & > p {
    font-size: 12.5px;
    font-weight: 600;
    line-height: 6px;
  }
`;
