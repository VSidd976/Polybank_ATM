import { forwardRef, type ForwardedRef, type ReactElement } from "react";
import { BANK_LOGOS, COMPANY_LOGO, type Card } from "./consts";
import { styled } from "@mui/material";
import { useMemoValue } from "@utils/hooks/useMemoValue";
import { formatCardNumber } from "@utils/format";

type Props = {
  card: Card;
  className?: string;
};

const BankCard = (
  { card, className }: Props,
  ref: ForwardedRef<HTMLDivElement>,
): ReactElement => {
  return (
    <CardComposite.Container className={className} ref={ref}>
      <CardComposite.Header {...card} />
      <CardComposite.CardNumber {...card} />
      <CardComposite.Footer {...card} />
    </CardComposite.Container>
  );
};

export default forwardRef(BankCard);

const Header = ({
  bank,
  transactionCompany,
}: Pick<Card, "bank" | "transactionCompany">): ReactElement => {
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
    ${({ theme }) => theme.palette.primary.light} 0.28%,
    ${({ theme }) => theme.palette.primary.main} 76.49%,
    ${({ theme }) => theme.palette.primary.dark} 99.51%
  );

  border-radius: 20px;
`;

const HeaderWrapper = styled("div")`
  display: flex;
  width: 100%;
  justify-content: space-between;
`;

const CardNumber = ({ number }: Pick<Card, "number">): ReactElement => {
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
  color: ${({ theme }) => theme.palette.primary.contrastText};
  font-weight: 500;
`;

const MagneticRectangle = styled("div")`
  background: #fff;
  width: 48.6px;
  height: 33.25px;
  border-radius: 6px;
`;

const Number = styled("span")`
  display: inline-block;
  font-size: 20px;
  text-shadow: 2px 2px 4px #00000069;
  margin-top: 5px;
`;

const Footer = ({
  ownerName,
  expDate,
  cvv,
}: Pick<Card, "cvv" | "ownerName" | "expDate">): ReactElement => {
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
    color: ${({ theme }) => theme.palette.info.contrastText};
    font-size: 10px;
    font-weight: 400;
  }
  p & > p {
    font-size: 12.5px;
    font-weight: 500;
    line-height: 6px;
  }
`;

const CardComposite = {
  Header,
  CardNumber,
  Footer,
  Container,
};
