import { useAtmApi, type DepositInfo } from "@api/AtmAPI";
import { BackButton as BackButton_ } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import InputBase from "@components/Input/Input";
import { BaseModal } from "@components/Modal";
import { Title as TitleBase } from "@components/Title/title";
import { styled } from "@mui/material";
import { PieChart } from "@mui/x-charts/PieChart";
import { useBoolean } from "@utils/hooks/useBoolean";
import { useMemoValue } from "@utils/hooks/useMemoValue";
import { useEffect, useRef, useState, type ReactElement } from "react";

const Deposits = (): ReactElement => {
  const [isOpen, modal] = useBoolean();
  return (
    <Container>
      <Wrapper>
        <BackButton />
        <Title>Manage your deposits</Title>
      </Wrapper>
      <Button txt="Create new deposit" onClick={modal.on} />
      <CreateModal isOpen={isOpen} onClose={modal.off} />
      <DepositsList />
    </Container>
  );
};

export default Deposits;

const CreateModal = ({
  isOpen,
  onClose,
}: {
  isOpen: boolean;
  onClose: () => void;
}): ReactElement => {
  const formRef = useRef<HTMLFormElement>(null);
  const [duration, setDuration] = useState("3");
  const [amount, setAmount] = useState("0");
  const api = useAtmApi({
    success: { redirectTo: "/main", text: "Operation successful" },
    failure: { text: "Failed to perform an operation" },
  });
  const onSubmit = () => {
    const { startDate, endDate } = calcDates(Number.parseInt(duration));
    const amount_ = Number.parseInt(amount);
    api?.newDeposit({ startDate, endDate, money: amount_ });
    formRef.current?.reset();
    onClose();
  };
  return (
    <BaseModal open={isOpen} onClose={onClose}>
      <ModalBody ref={formRef} onSubmit={onSubmit}>
        <TitleBase>Create a new deposit</TitleBase>
        <SubTitle>(0.1% per annum)</SubTitle>
        <InputWrapper>
          <SubTitle>Start amount</SubTitle>
          <Input type="number" onChange={setAmount} value={amount} min={1} />
        </InputWrapper>
        <InputWrapper>
          <SubTitle>Duration in month</SubTitle>
          <Input
            type="number"
            onChange={setDuration}
            value={duration}
            min={3}
            max={12}
          />
        </InputWrapper>
        <BaseButton type="submit" txt="Submit" />
      </ModalBody>
    </BaseModal>
  );
};

const calcDates = (duration: number) => {
  const today = new Date();

  const startDate = today.toISOString().split("T")[0];

  const endDateObj = new Date();
  endDateObj.setDate(today.getDate() + duration);

  const endDate = endDateObj.toISOString().split("T")[0];

  return { startDate, endDate };
};

const Input = styled(InputBase)``;

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

const InputWrapper = styled("div")`
  display: flex;
  flex-direction: column;
  align-self: flex-start;
`;

const SubTitle = styled("strong")`
  font-size: 18px;
  font-weight: 200;
`;

const Button = styled(BaseButton)`
  width: fit-content;
`;

const useDeposits = (): DepositInfo[] => {
  const [items, setItems] = useState<DepositInfo[]>([]);
  const api = useAtmApi();
  useEffect(() => {
    api?.getAllDeposits().then(setItems);
  }, []);
  return items;
};

const DepositsList = (): ReactElement => {
  const deposits = useDeposits();
  return (
    <>
      {deposits.map((d) => (
        <Deposit startDate={d.startDate} endDate={d.endDate} total={d.money} />
      ))}
    </>
  );
};

const Deposit = ({
  endDate,
  startDate,
  total,
}: {
  startDate: string;
  endDate: string;
  total: number;
}) => {
  return (
    <Card>
      <Donut startDate={startDate} endDate={endDate} />
      <Text>
        <span>End date: {endDate}</span>
        <span>End total: {total}$</span>
      </Text>
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
  flex-direction: column;
`;

const Donut = ({
  startDate,
  endDate,
}: {
  startDate: string;
  endDate: string;
}): ReactElement => {
  const value = useMemoValue(
    (_start, _end) => {
      const now = Date.now();
      const start = Date.parse(_start);
      const end = Date.parse(_end);

      if (now >= end) return 0;
      if (now <= start) return 100;

      return ((end - now) / (end - start)) * 100;
    },
    [startDate, endDate],
  );
  return (
    <PieChart
      series={[
        {
          ...seriesSettings,
          data: [{ value: 100 - value }, { value }],
        },
      ]}
      {...settings}
    />
  );
};

const seriesSettings = { innerRadius: 12, outerRadius: 20, startAngle: 0 };

const settings = {
  margin: { right: 5 },
  width: 40,
  height: 40,
  hideLegend: true,
  colors: ["#01B2AC", "gray"],
};

const Title = styled(TitleBase)`
  justify-self: center;
  position: absolute;
  left: 50%;
  transform: translateX(-50%);
`;

const BackButton = styled(BackButton_)`
  position: relative;
  max-height: fit-content;
  top: 0;
  left: 0;
`;

const Wrapper = styled("div")`
  display: flex;
  gap: 12px;
  width: 100%;
  max-height: fit-content;
  position: relative;
  align-items: center;
`;

const Container = styled("div")`
  width: 100%;
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 15px;
  max-width: 100vw;
  padding: 16px;
`;
