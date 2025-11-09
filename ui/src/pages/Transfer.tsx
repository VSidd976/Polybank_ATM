import AtmAPI from "@api/AtmAPI";
import type { Card } from "@components/BankCard/consts";
import { BackButton } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import Input from "@components/Input/Input";
import { styled } from "@mui/material";
import { useCard } from "@utils/stores/cardStore";
import {
  useCallback,
  useState,
  type FormEvent,
  type ReactElement,
} from "react";
import { useNavigate, type NavigateFunction } from "react-router-dom";
import { toast } from "react-toastify";

const AMOUNT_INPUT = "amount";
const CARD_NUMBER = "card-number";

const onFormSubmit = (
  e: FormEvent<HTMLFormElement>,
  card: Card | undefined,
  navigate: NavigateFunction,
): void => {
  e.preventDefault();
  const formData = new FormData(e.currentTarget);
  const amount = formData.get(AMOUNT_INPUT) as string;
  const cardNumber = formData.get(CARD_NUMBER) as string;
  if (!card) return void toast("No card inserted");
  if (!amount || !cardNumber || cardNumber.length !== 16)
    return void toast("Invalid from data");

  AtmAPI.of(card)
    .transferMoney(Number.parseFloat(amount), cardNumber)
    .then(() => {
      toast.success("Operation successful");
      navigate("/main");
    })
    .catch(() => {
      toast("Operation went wrong");
    });
};

const Transfer = (): ReactElement => {
  const [value, setValue] = useState("");
  const navigate = useNavigate();
  const { card } = useCard();

  const handleChange = (v_: string) => {
    let v = v_.replace(/\D/g, "");
    v = v.slice(0, 16);
    setValue(v);
  };

  const onSubmit = useCallback(
    (e: FormEvent<HTMLFormElement>) => onFormSubmit(e, card, navigate),
    [card, navigate],
  );
  return (
    <Container>
      <BackButton />
      <Form onSubmit={onSubmit}>
        <Input name={AMOUNT_INPUT} type="number" min={0} placeholder="Amount" />
        <Input
          min={0}
          value={value}
          onChange={handleChange}
          name={CARD_NUMBER}
          placeholder="Card number"
          inputMode="numeric"
          maxLength={16}
        />
        <BaseButton type="submit" txt="Submit" />
      </Form>
    </Container>
  );
};

export default Transfer;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  position: relative;
  overflow: hidden;
`;

const Form = styled("form")`
  display: flex;
  flex-direction: column;
  gap: 12px;
`;
