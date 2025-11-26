import AtmAPI, { useAtmApi } from "@api/AtmAPI";
import { BackButton } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import Input from "@components/Input/Input";
import { Title as Title_ } from "@components/Title/title";
import { styled } from "@mui/material";
import { withProps } from "@utils/withProps";
import {
  useCallback,
  useState,
  type FormEvent,
  type ReactElement,
} from "react";
import { toast } from "react-toastify";

const AMOUNT_INPUT = "amount";
const CARD_NUMBER = "card-number";

const onFormSubmit = (
  e: FormEvent<HTMLFormElement>,
  api: AtmAPI | null,
): void => {
  e.preventDefault();
  const formData = new FormData(e.currentTarget);
  const amount = formData.get(AMOUNT_INPUT) as string;
  const cardNumber = formData.get(CARD_NUMBER) as string;
  if (!api) throw Error("No card inserted");
  if (!amount || !cardNumber || cardNumber.length !== 16)
    return void toast.error("Invalid form data");

  api.transferMoney(Number.parseFloat(amount), cardNumber);
};

const Transfer = (): ReactElement => {
  const [value, setValue] = useState("");
  const api = useAtmApi({
    success: { text: "Operation successful", redirectTo: "/main/success" },
    failure: { text: "Operation failure" },
  });

  const handleChange = (v_: string) => {
    let v = v_.replace(/\D/g, "");
    v = v.slice(0, 16);
    setValue(v);
  };

  const onSubmit = useCallback(
    (e: FormEvent<HTMLFormElement>) => onFormSubmit(e, api),
    [api],
  );
  return (
    <Container>
      <BackButton />
      <Form onSubmit={onSubmit}>
        <Title>Transfer money</Title>
        <CardNumberInput value={value} onChange={handleChange} />
        <Input name={AMOUNT_INPUT} type="number" min={0} placeholder="Amount" />
        <BaseButton type="submit" txt="Submit" />
      </Form>
    </Container>
  );
};

const CardNumberInput = withProps(Input, {
  min: 0,
  name: CARD_NUMBER,
  placeholder: "Card number",
  inputMode: "numeric",
  maxLength: 16,
} as const);

const Title = styled(Title_)`
  text-align: center;
`;

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
