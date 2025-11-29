import {
  useAtmApi,
  type DepositProductResponseDto,
  type DepositResponseDto,
} from "@api/AtmAPI";
import { BackButton as BackButton_ } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import InputBase from "@components/Input/Input";
import { BaseModal } from "@components/Modal";
import { Title as TitleBase } from "@components/Title/title";
import { Select, styled } from "@mui/material";
import MenuItem from "@mui/material/MenuItem";
import { formatDate } from "@utils/format";
import { useAccountInfo } from "@utils/hooks/useAccountInfo";
import { useBoolean } from "@utils/hooks/useBoolean";
import { useEffect, useRef, useState, type ReactElement } from "react";
import { toast } from "react-toastify";

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

const useProducts = (): DepositProductResponseDto[] => {
  const api = useAtmApi();
  const [products, setProducts] = useState<DepositProductResponseDto[]>([]);
  useEffect(() => {
    api?.depositProducts().then(setProducts);
  }, [api]);
  return products;
};

const CreateModal = ({
  isOpen,
  onClose,
}: {
  isOpen: boolean;
  onClose: () => void;
}): ReactElement => {
  const formRef = useRef<HTMLFormElement>(null);
  const products = useProducts();
  const [amount, setAmount] = useState("0");
  const [productId, setProductId] = useState(products.at(0)?.id ?? "0");
  const api = useAtmApi({
    success: { redirectTo: "/main/success", text: "Operation successful" },
    failure: { text: "Failed to perform an operation" },
  });
  const accountInfo = useAccountInfo();
  const onSubmit = () => {
    const amount_ = Number.parseInt(amount);
    if (!productId) return void toast.warning("Choose type of deposit!");
    api?.newDeposit({ productId: productId, amount: amount_ });
    formRef.current?.reset();
    onClose();
  };
  return (
    <BaseModal open={isOpen} onClose={onClose}>
      <ModalBody ref={formRef} onSubmit={onSubmit}>
        <TitleBase>Create a new deposit</TitleBase>
        <InputWrapper>
          <SubTitle>Start amount</SubTitle>
          <Input
            type="number"
            onChange={setAmount}
            value={amount}
            min={1}
            max={accountInfo?.balance}
          />
        </InputWrapper>
        <InputWrapper>
          <SubTitle>Deposit Type</SubTitle>
          <Select
            value={productId}
            sx={{ color: "#fff" }}
            onChange={(p) => setProductId(p.target.value)}
          >
            {products.map((p) => (
              <MenuItem sx={{ color: "#fff" }} key={p.name} value={p.id}>
                {p.name} ({p.interestRate}%)
              </MenuItem>
            ))}
          </Select>
        </InputWrapper>
        <BaseButton type="submit" txt="Submit" />
      </ModalBody>
    </BaseModal>
  );
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

const useDeposits = (): DepositResponseDto[] => {
  const [items, setItems] = useState<DepositResponseDto[]>([]);
  const api = useAtmApi();
  useEffect(() => {
    api?.getAllDeposits().then(setItems);
  }, [api]);
  return items;
};

const DepositsList = (): ReactElement => {
  const deposits = useDeposits();
  return (
    <>
      {!deposits.length && <Text>No active deposits yet</Text>}
      {deposits.map((d) => (
        <Deposit
          key={d.id}
          startDate={d.startDate}
          endDate={d.endDate}
          total={d.money}
        />
      ))}
    </>
  );
};

const Deposit = ({
  startDate,
  total,
  key,
}: {
  key?: string;
  startDate: string;
  endDate: string;
  total: number;
}) => {
  return (
    <Card key={key}>
      <Text>
        <span>Opened at: {formatDate(startDate)}</span>
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
  color: #fff;
  flex-direction: column;
`;

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
