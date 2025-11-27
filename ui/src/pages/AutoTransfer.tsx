import AtmAPI, { useAtmApi, type AutoTransferResponseDto } from "@api/AtmAPI";
import { BackButton } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import Input from "@components/Input/Input";
import { BaseModal } from "@components/Modal";
import { Title as Title_ } from "@components/Title/title";
import { capitalize, Select, styled, ThemeProvider } from "@mui/material";
import MenuItem from "@mui/material/MenuItem";
import { DatePicker } from "@mui/x-date-pickers/DatePicker";
import { useBoolean } from "@utils/hooks/useBoolean";
import dayjs from "dayjs";
import { withProps } from "@utils/withProps";
import { AdapterDayjs } from "@mui/x-date-pickers/AdapterDayjs";
import {
  useCallback,
  useEffect,
  useState,
  type FormEvent,
  type ReactElement,
} from "react";
import { toast } from "react-toastify";
import { LocalizationProvider } from "@mui/x-date-pickers/LocalizationProvider";
import { datePickerTheme } from "@root/datepickerTheme";

const AMOUNT_INPUT = "threshold-input";
const FREQUENCY_INPUT = "frequency-input";
const NEXT_DATE = "next-transfer-date";
const CARD_NUMBER = "card-number";

const onFormSubmit = (
  e: FormEvent<HTMLFormElement>,
  api: AtmAPI | null,
): void => {
  e.preventDefault();
  const formData = new FormData(e.currentTarget);
  const amount = formData.get(AMOUNT_INPUT) as string;
  const frequency = formData.get(FREQUENCY_INPUT) as string;
  const nextDate = formData.get(NEXT_DATE) as string;
  const cardNumber = formData.get(CARD_NUMBER) as string;
  if (!api) throw Error("No card inserted");
  if (!amount || !cardNumber || cardNumber.length !== 16)
    return void toast.error("Invalid form data");
  api.createAutoTransfer(
    Number.parseFloat(amount),
    cardNumber,
    nextDate,
    frequency,
  );
};

const AutoTransfers = (): ReactElement => {
  const [isOpen, modal] = useBoolean(false);
  return (
    <Container>
      <BackButton />
      <Title>Auto-Tranfers</Title>
      <BaseButton txt="Add new autotransfer" onClick={modal.on} />
      <AutoTransfersList />
      <CreationForm isOpen={isOpen} onClose={modal.off} />
    </Container>
  );
};

const useAutoTransfers = (): [
  AutoTransferResponseDto[],
  (idx: number) => void,
] => {
  const [autoTransfers, setAutoTransfers] = useState(
    [] as AutoTransferResponseDto[],
  );
  const api = useAtmApi();
  useEffect(() => {
    api?.allAutoTransfers().then((v) => setAutoTransfers(v));
  }, []);
  const onDelete = (idx: number) => {
    setAutoTransfers((prev) => prev.filter((_, _idx) => _idx !== idx));
  };
  return [autoTransfers, onDelete];
};

const AutoTransfersList = (): ReactElement => {
  const [autotransfers, onItemDelete] = useAutoTransfers();
  const api = useAtmApi({
    success: { text: "Operation successful" },
    failure: { text: "Operation failure" },
  });
  const onDelete = (id: string, idx: number): void => {
    api?.removeAutoTransfer(id).then(() => onItemDelete(idx));
  };
  return (
    <>
      {!autotransfers.length && <Text>No transfers yet</Text>}
      {autotransfers.map((l, idx) => (
        <AutoTransfer {...l} onDelete={() => onDelete(l.id, idx)} />
      ))}
    </>
  );
};

const AutoTransfer = ({
  id,
  targetCard,
  nextDate,
  frequency,
  onDelete,
}: AutoTransferResponseDto & {
  onDelete: () => void;
}): ReactElement => {
  return (
    <Card key={id}>
      <Wrapper>
        <Text>Target card: {targetCard}</Text>
        <Text>Next tranfer: {nextDate} </Text>
        <Text>Frequency: {capitalize(frequency)} </Text>
      </Wrapper>
      <BaseButton txt="Remove" onClick={onDelete} />
    </Card>
  );
};

const Wrapper = styled("div")`
  display: flex;
  gap: 12px;
  flex-direction: column;
`;

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

const OPTIONS = ["once", "weekly", "monthly", "yearly"];

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
        <Input name={AMOUNT_INPUT} type="number" min={0} placeholder="Amount" />
        <CardNumberInput value={value} onChange={handleChange} />
        <Select
          sx={{ color: "#fff" }}
          required
          name={FREQUENCY_INPUT}
          defaultValue={OPTIONS[0]}
        >
          {OPTIONS.map((opt) => (
            <MenuItem value={opt} key={opt} sx={{ color: "#fff" }}>
              {capitalize(opt)}
            </MenuItem>
          ))}
        </Select>
        <CustomDatePicker />
        <BaseButton type="submit" txt="Submit" />
      </ModalBody>
    </BaseModal>
  );
};

const CustomDatePicker = (): ReactElement => {
  return (
    <LocalizationProvider dateAdapter={AdapterDayjs}>
      <ThemeProvider theme={datePickerTheme}>
        <DatePicker
          minDate={dayjs()}
          format="YYYY-MM-DD"
          name={NEXT_DATE}
          sx={{
            "*": { color: "#fff !important" },
            color: "#fff !important",
            "button:not(.Mui-disabled)": { color: "#fff !important" },
            ".MuiPaper-root": {
              backgroundColor: "#121212",
              color: "white",
            },
          }}
        />
      </ThemeProvider>
    </LocalizationProvider>
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

export default AutoTransfers;

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
