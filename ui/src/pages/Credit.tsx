import {
  useAtmApi,
  type CreditProductResponseDto,
  type CreditResponseDto,
} from "@api/AtmAPI";
import { BackButton as BackButton_ } from "@components/Button/BackButton";
import BaseButton from "@components/Button/Button";
import InputBase from "@components/Input/Input";
import { BaseModal } from "@components/Modal";
import { Title as TitleBase } from "@components/Title/title";
import { Select, styled } from "@mui/material";
import MenuItem from "@mui/material/MenuItem";
import { useBoolean } from "@utils/hooks/useBoolean";
import { useEffect, useRef, useState, type ReactElement } from "react";
import { toast } from "react-toastify";

const Credits = (): ReactElement => {
  const [isOpen, modal] = useBoolean();
  return (
    <Container>
      <Wrapper>
        <BackButton />
        <Title>Manage your credits</Title>
      </Wrapper>
      <Button txt="Open new credit" onClick={modal.on} />
      <CreateModal isOpen={isOpen} onClose={modal.off} />
      <CreditsList />
    </Container>
  );
};

export default Credits;

const useProducts = (): CreditProductResponseDto[] => {
  const api = useAtmApi();
  const [products, setProducts] = useState<CreditProductResponseDto[]>([]);
  useEffect(() => {
    api?.creditProducts().then(setProducts);
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
        <TitleBase>New credit</TitleBase>
        <InputWrapper>
          <SubTitle>Amount</SubTitle>
          <Input type="number" onChange={setAmount} value={amount} min={1} />
        </InputWrapper>
        <InputWrapper>
          <SubTitle>Credit Type</SubTitle>
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

const useCredits = (): CreditResponseDto[] => {
  const [items, setItems] = useState<CreditResponseDto[]>([]);
  const api = useAtmApi();
  useEffect(() => {
    api?.getAllCredits().then(setItems);
  }, [api]);
  return items;
};

const CreditsList = (): ReactElement => {
  const credits = useCredits();
  return (
    <>
      {credits.map((c) => (
        <Credit
          key={c.id}
          startDate={c.openedAt}
          remainingAmount={c.remainingAmount}
        />
      ))}
    </>
  );
};

const Credit = ({
  startDate,
  remainingAmount,
  key,
}: {
  key?: string;
  startDate: string;
  remainingAmount: number;
}) => {
  return (
    <Card key={key}>
      <Text>
        <span>Opened at: {startDate}</span>
        <span>Remaining to close: {remainingAmount}$</span>
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
