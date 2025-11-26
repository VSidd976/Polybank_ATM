import AtmAPI, {
  useAtmApi,
  type LeftOverHandlerResponseDto,
} from "@api/AtmAPI";
import { BackButton } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import Input from "@components/Input/Input";
import { BaseModal } from "@components/Modal";
import { Title as Title_ } from "@components/Title/title";
import { Select, styled } from "@mui/material";
import MenuItem from "@mui/material/MenuItem";
import { useBoolean } from "@utils/hooks/useBoolean";
import { withProps } from "@utils/withProps";
import {
  useCallback,
  useEffect,
  useState,
  type FormEvent,
  type ReactElement,
} from "react";
import { toast } from "react-toastify";

const TRESHOLD_INPUT = "treshold-input";
const CARD_NUMBER = "card-number";

const onFormSubmit = (
  e: FormEvent<HTMLFormElement>,
  api: AtmAPI | null,
): void => {
  e.preventDefault();
  const formData = new FormData(e.currentTarget);
  const amount = formData.get(TRESHOLD_INPUT) as string;
  const cardNumber = formData.get(CARD_NUMBER) as string;
  if (!api) throw Error("No card inserted");
  if (!amount || !cardNumber || cardNumber.length !== 16)
    return void toast.error("Invalid form data");
  api.createLeftoverHandling(Number.parseFloat(amount), cardNumber);
};

const LeftOvers = (): ReactElement => {
  const [isOpen, modal] = useBoolean(false);
  return (
    <Container>
      <BackButton />
      <Title>Leftover handling</Title>
      <BaseButton txt="Add new handling" onClick={modal.on} />
      <LeftOversList />
      <CreationForm isOpen={isOpen} onClose={modal.off} />
    </Container>
  );
};

const useLeftovers = (): [
  LeftOverHandlerResponseDto[],
  (idx: number) => void,
] => {
  const [leftovers, setLeftovers] = useState(
    [] as LeftOverHandlerResponseDto[],
  );
  const api = useAtmApi();
  useEffect(() => {
    api?.allLeftOverHandlers().then((v) => setLeftovers(v));
  }, []);
  const onDelete = (idx: number) => {
    setLeftovers((prev) => prev.filter((_, _idx) => _idx !== idx));
  };
  return [leftovers, onDelete];
};

const LeftOversList = (): ReactElement => {
  const [leftovers, onItemDelete] = useLeftovers();
  const api = useAtmApi({
    success: { text: "Operation successful", redirectTo: "/main/success" },
    failure: { text: "Operation failure" },
  });
  const onDelete = (id: string, idx: number): void => {
    api?.removeLeftoverHandler(id).then(() => onItemDelete(idx));
  };
  return (
    <>
      {leftovers.map((l, idx) => (
        <LeftOver {...l} onDelete={() => onDelete(l.id, idx)} />
      ))}
    </>
  );
};

const LeftOver = ({
  id,
  targetCard,
  treshold,
  onDelete,
}: LeftOverHandlerResponseDto & {
  onDelete: () => void;
}): ReactElement => {
  return (
    <Card key={id}>
      <Text>Target card: {targetCard}</Text>
      <Text>Treshold: {treshold}</Text>
      <BaseButton txt="Remove" onClick={onDelete} />
    </Card>
  );
};

const Card = styled("div")`
  display: flex;
  background: ${({ theme }) => theme.palette.background.paper};
  max-width: fit-content;
  padding: 15px;
  border-radius: 12px;
  gap: 12px;
  & > * {
    flex: unset !important;
  }
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

const Text = styled("p")`
  display: flex;
  color: #fff;
  flex-direction: column;
`;

const OPTIONS = [10, 50, 100];

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
        <Title>Create new handling</Title>
        <CardNumberInput value={value} onChange={handleChange} />
        <Select
          sx={{ color: "#fff" }}
          required
          name={TRESHOLD_INPUT}
          defaultValue={OPTIONS[0]}
        >
          {OPTIONS.map((opt) => (
            <MenuItem value={opt} key={opt} sx={{ color: "#fff" }}>
              {opt}
            </MenuItem>
          ))}
        </Select>
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
