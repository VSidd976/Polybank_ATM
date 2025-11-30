import { useAtmApi } from "@api/AtmAPI";
import { BackButton } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import Cash_ from "@components/Cash/Cash";
import { CASH_NOMINALS, type Nominal } from "@components/Cash/const";
import Input_ from "@components/Input/Input";
import { Fade, styled } from "@mui/material";
import { useAccountInfo } from "@utils/hooks/useAccountInfo";
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

function calcNominals(amount: number): Record<Nominal, number> {
  return Object.keys(CASH_NOMINALS)
    .sort((a, b) => (Number.parseInt(a) > Number.parseInt(b) ? -1 : 1))
    .reduce((acc, curr) => {
      const n = Math.floor(amount / Number.parseInt(curr));
      amount -= n * Number.parseInt(curr);
      if (!n) return acc;
      return { ...acc, [curr]: n };
    }, {});
}

const inputName = "cash-out-input";

function onFormSubmit(e: FormEvent<HTMLFormElement>): number | undefined {
  e.preventDefault();
  const value = Object.fromEntries(new FormData(e.currentTarget))[
    inputName
  ] as string;
  e.currentTarget.reset();
  if (!value || !Number.isInteger(Number.parseInt(value))) {
    toast.error("Invalid amount input");
    return;
  }
  return Number.parseInt(value);
}

const CashOut = (): ReactElement => {
  const [isAnimated, setAnimated] = useBoolean();
  const api = useAtmApi({
    onSuccess: () => {
      setAnimated.on();
    },
    failure: { text: "Can't perform the operation" },
  });
  const [nominals, setNominals] = useState<Record<Nominal, number>>();
  const afterSubmit = useCallback(
    (v: number | undefined) => {
      if (!v || !api) return;
      api.cashOut(v).then(() => setNominals(calcNominals(v)));
    },
    [api],
  );
  return (
    <Container>
      <BackButton />
      <Fade in={isAnimated}>
        <div>{nominals ? <Nominals nominals={nominals} /> : <></>}</div>
      </Fade>
      <Fade in={!isAnimated}>
        <div>
          <FormBlock onAfterSubmit={afterSubmit} />
        </div>
      </Fade>
    </Container>
  );
};

const Nominals = ({
  nominals,
}: {
  nominals: Record<Nominal, number>;
}): ReactElement => {
  let globalIndex = 0;
  return (
    <>
      {Object.entries(nominals).map(([nominal, amount], idx) =>
        Array.from({ length: amount }).map((_, i) => {
          const nom = Number.parseInt(nominal);
          return (
            <Cash
              $index={globalIndex++}
              key={`nominal-${idx}-${i}`}
              nominal={nom}
            />
          );
        }),
      )}
    </>
  );
};

const useCashAmount = (): number => {
  const [cashAmount, setAmount] = useState(0);
  const api = useAtmApi();
  useEffect(() => {
    api?.cashInfo().then(setAmount);
  }, [api]);
  return cashAmount;
};

const FormBlock = ({
  onAfterSubmit,
}: {
  onAfterSubmit?: (val: number | undefined) => void;
}): ReactElement => {
  const [value, setValue] = useState<string>();
  const cashAmount = useCashAmount();
  const accountInfo = useAccountInfo();
  const onSubmit = useCallback(
    (e: FormEvent<HTMLFormElement>) => {
      const val = onFormSubmit(e);
      onAfterSubmit?.(val);
    },
    [onAfterSubmit],
  );
  return (
    <Form onSubmit={onSubmit}>
      <NominalsInfo>ATM has {cashAmount}$ in cash right now.</NominalsInfo>
      <NominalsInfo>
        Available nominals: {Object.keys(CASH_NOMINALS).join(", ")}
      </NominalsInfo>
      <Input max={accountInfo?.balance} onChange={setValue} />
      <BaseButton disabled={!value} txt="Submit" type="submit" />
    </Form>
  );
};

export default CashOut;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  position: relative;
  overflow: hidden;
`;

const NominalsInfo = styled("span")`
  text-transform: uppercase;
  color: #bfbfbf;
  text-wrap: nowrap;
  font-size: 26px;
  font-weight: 200;
`;

const Cash = styled(Cash_)<{ $index: number }>`
  opacity: 0;
  position: absolute;
  animation: 1.5s slideIntoFrame ease forwards;
  animation-delay: ${({ $index }) => $index * 1_000}ms;
  @keyframes slideIntoFrame {
    0% {
      bottom: 120vh;
      opacity: 1;
    }
    100% {
      bottom: 50%;
      opacity: 1;
    }
  }
`;

const Input = styled(
  withProps(Input_, {
    type: "number",
    placeholder: "Enter Amount",
    min: 1,
    step: 1,
    name: inputName,
  } as const),
)`
  padding: 20px 35px;
  &::-webkit-outer-spin-button,
  &::-webkit-inner-spin-button {
    -webkit-appearance: none;
    margin: 0;
  }
  &[type="number"] {
    -moz-appearance: textfield;
  }
`;

const Form = styled("form")`
  display: flex;
  align-items: center;
  flex-direction: column;
  gap: 12px;
`;
