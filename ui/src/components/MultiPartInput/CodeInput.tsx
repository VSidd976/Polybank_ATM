import { styled } from "@mui/material";
import { type ReactElement } from "react";
import InputPart from "./InputPart";
import { useInputSequance } from "@utils/hooks/useInputSequance";
import BaseButton_ from "@components/Button/Button";
import { InputStoreProvider } from "@utils/stores/inputStore";

type Props = {
  length: number;
};

const CodeInput_ = ({ length }: Props): ReactElement => {
  const [inputs, { onPrev }] = useInputSequance(length);
  return (
    <Form>
      {inputs.map(InputPart)}
      <Button txt="<" onClick={onPrev} />
    </Form>
  );
};

const CodeInput = ({ length }: Props): ReactElement => {
  return (
    <InputStoreProvider amount={length}>
      <CodeInput_ length={length} />
    </InputStoreProvider>
  );
};

export default CodeInput;

const Form = styled("form")`
  display: flex;
  height: min-content;
  gap: 10px;
`;

const Button = styled(BaseButton_)``;
