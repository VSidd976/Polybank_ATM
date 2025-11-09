import AtmAPI from "@api/AtmAPI";
import type { Card } from "@components/BankCard/consts";
import { BackButton } from "@components/Button/BackButton";
import Cash_ from "@components/Cash/Cash";
import { CASH_NOMINALS, type Nominal } from "@components/Cash/const";
import { styled } from "@mui/material";
import { useCard } from "@utils/stores/cardStore";
import { useCallback, useEffect, useState, type ReactElement } from "react";
import { toast } from "react-toastify";

const OPTIONS = Object.keys(CASH_NOMINALS);

const ANIMATION_DURATION = 2_500;

const useInsert = (): {
  inserted: number | undefined;
  insert: (n: Nominal) => void;
} => {
  const [inserted, setInserted] = useState<Nominal | undefined>(undefined);
  const insert = useCallback((n: Nominal) => {
    setInserted((prev) => {
      if (prev) return prev;
      setTimeout(() => setInserted(undefined), ANIMATION_DURATION);
      return n;
    });
  }, []);
  return { inserted, insert };
};

function sendReq(card: Card | undefined, amount: number): void {
  if (!card) return;
  AtmAPI.of(card)
    .putMoney(amount)
    .then(() => toast.success("Operation successful"))
    .catch(() =>
      toast(
        "Opeartion went wrong, please leave your request on our contact line",
      ),
    );
}

const AddMoney = (): ReactElement => {
  const { insert, inserted } = useInsert();
  const [total, updateTotal] = useState<number>(0);
  const { card } = useCard();

  const onPutMoney = useCallback(() => sendReq(card, total), [card, total]);

  useEffect(() => {
    if (inserted) updateTotal((s) => s + inserted);
  }, [inserted]);

  return (
    <Container>
      <BackButton onBeforeClick={onPutMoney} />
      <Total>Total inserted: {total}</Total>
      {inserted ? (
        <InsertableCash $isInserted={inserted} nominal={inserted} />
      ) : (
        <></>
      )}
      {OPTIONS.map((n, i) => (
        <Cash
          key={n}
          nominal={Number.parseInt(n)}
          $index={i}
          onClick={insert}
        />
      ))}
    </Container>
  );
};

export default AddMoney;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  position: relative;
  overflow: hidden;
`;

const Total = styled("span")`
  text-transform: uppercase;
  color: #bfbfbf;
  font-size: 32px;
  font-weight: 200;
`;

const InsertableCash = styled(Cash_)<{ $isInserted: number | undefined }>`
  ${({ $isInserted }) =>
    $isInserted ? `animation: insert ${ANIMATION_DURATION}ms;` : ""}
  position: absolute;
  bottom: 50%;
  right: 50%;
  opacity: 0;
  transform: translate(50%, -50%) rotate(90deg);
  z-index: 3;

  @keyframes insert {
    0% {
      bottom: 50%;
    }
    10% {
      opacity: 1;
    }
    100% {
      bottom: 100%;
    }
  }
`;

const Cash = styled(Cash_)<{ $index: number }>`
  position: absolute;
  user-select: none;
  bottom: -${({ $index }) => $index * 10}px;
  right: 45%;
  transform: translate(
      ${({ $index }) => $index * 45}px,
      ${({ $index }) => Math.pow($index - 3, 2) * 5}px
    )
    rotate(${({ $index }) => 45 + $index * (120 / OPTIONS.length)}deg);
  cursor: pointer;
  transition: all 0.3s ease;
  z-index: 3;
  &:hover {
    scale: 1.05;
  }
  &:focus,
  &:active {
    scale: 1;
  }
`;
