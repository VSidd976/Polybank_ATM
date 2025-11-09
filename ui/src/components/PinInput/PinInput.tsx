import { styled } from "@mui/material";
import { type ReactElement } from "react";
import InputPart from "./InputPart";
import { useInputSequance } from "@utils/hooks/useInputSequance";
import BaseButton_ from "@components/Button/Button";
import { InputStoreProvider, useInputsStore } from "@utils/stores/inputStore";

type Props = {
  length: number;
};

export const PIN_INPUT = "pin-input-field";

const CodeInput_ = (): ReactElement => {
  const { values, selectedIdx, onPrev } = useInputsStore();
  const inputs = useInputSequance(values, selectedIdx);
  return (
    <Wrapper id={PIN_INPUT}>
      {inputs.map(InputPart)}
      <Button txt="<" onClick={onPrev} />
    </Wrapper>
  );
};

const PinInput = ({ length }: Props): ReactElement => {
  return (
    <InputStoreProvider amount={length}>
      <CodeInput_ />
    </InputStoreProvider>
  );
};

export default PinInput;

const Wrapper = styled("fieldset")`
  display: flex;
  height: min-content;
  border: none;
  gap: 10px;
`;

const Button = styled(BaseButton_)`
  &::before {
    padding: 3px;
  }
`;
