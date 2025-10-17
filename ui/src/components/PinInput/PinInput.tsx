import { styled } from "@mui/material";
import { type ReactElement } from "react";
import InputPart from "./InputPart";
import { useInputSequance } from "@utils/hooks/useInputSequance";
import BaseButton_ from "@components/Button/Button";
import { InputStoreProvider, useInputsStore } from "@utils/stores/inputStore";

type Props = {
  length: number;
};

const CodeInput_ = (): ReactElement => {
  const { values, selectedIdx, onPrev } = useInputsStore();
  const inputs = useInputSequance(values, selectedIdx);
  return (
    <Form>
      {inputs.map(InputPart)}
      <Button txt="<" onClick={onPrev} />
    </Form>
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

const Form = styled("form")`
  display: flex;
  height: min-content;
  gap: 10px;
`;

const Button = styled(BaseButton_)`
  &::before {
    padding: 3px;
  }
`;
