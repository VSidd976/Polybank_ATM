import AtmAPI, { useAtmApi } from "@api/AtmAPI";
import { BackButton } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import Input from "@components/Input/Input";
import { BaseModal } from "@components/Modal";
import { Title as Title_ } from "@components/Title/title";
import { styled } from "@mui/material";
import { useBoolean } from "@utils/hooks/useBoolean";
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

const LeftOvers = (): ReactElement => {
  const [isOpen, modal] = useBoolean(false);
  return (
    <Container>
      <BackButton />
      <Title>Leftover handling</Title>
      <BaseButton txt="Add new handling" onClick={modal.on} />
      <CreationForm isOpen={isOpen} onClose={modal.off} />
    </Container>
  );
};

const CreationForm = ({
  isOpen,
  onClose,
}: {
  isOpen: boolean;
  onClose: () => void;
}) => {
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
    <BaseModal open={isOpen} onClose={onClose}>
      <ModalBody onSubmit={onSubmit}>
        <CardNumberInput value={value} onChange={handleChange} />
        <Input name={AMOUNT_INPUT} type="number" min={0} placeholder="Amount" />
        <BaseButton type="submit" txt="Submit" />
      </ModalBody>
    </BaseModal>
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

export default LeftOvers;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  gap: 12px;
  position: relative;
  overflow: hidden;
`;

const ModalBody = styled("form")`
  padding: 25px;
  display: flex;
  gap: 15px;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  background: ${({ theme }) => theme.palette.background.paper};
  color: #fff;
  position: relative;
  border-radius: 10px;
  z-index: 1;

  &::before {
    content: "";
    position: absolute;
    inset: 0;
    border-radius: 10px;
    padding: 2px;
    background: linear-gradient(
      270deg,
      ${({ theme }) => theme.palette.secondary.main},
      ${({ theme }) => theme.palette.primary.light},
      ${({ theme }) => theme.palette.secondary.main}
    );
    -webkit-mask:
      linear-gradient(#fff 0 0) content-box,
      linear-gradient(#fff 0 0);
    -webkit-mask-composite: xor;
    mask-composite: exclude;
    z-index: 0;
    background-size: 600% 600%;
    animation: gradientMove 4s linear infinite;
  }

  @keyframes gradientMove {
    0% {
      background-position: 0% 50%;
    }
    50% {
      background-position: 100% 50%;
    }
    100% {
      background-position: 0% 50%;
    }
  }
`;
