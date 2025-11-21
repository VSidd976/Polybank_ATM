import PinInput from "@components/PinInput/PinInput";
import NoPeeking from "@assets/no-peek.svg";
import { styled } from "@mui/material";
import BaseButton from "@components/Button/Button";
import type { FormEvent } from "react";
import { toast } from "react-toastify";
import AtmAPI, { useAtmApi } from "@api/AtmAPI";

const badPinNotify = () =>
  toast.error("Oops, looks like your pin is invalid", { type: "warning" });

const onSubmit = async (
  e: FormEvent<HTMLFormElement>,
  api: AtmAPI | null,
): Promise<void> => {
  e.preventDefault();
  if (!api) return;
  const pin = Object.values(
    Object.fromEntries(new FormData(e.currentTarget)),
  ).reduce((acc, curr) => (typeof curr === "string" ? acc + curr : acc), "");

  if (typeof pin !== "string" || pin.length != 4) {
    badPinNotify();
    return;
  }

  await api.inputPIN(pin);
};

const Pin = () => {
  const api = useAtmApi({
    sucess: { redirectTo: "/main" },
    onFailure: badPinNotify,
  });
  return (
    <Container onSubmit={(e) => onSubmit(e, api)}>
      <Image src={NoPeeking} width={80} />
      <Title>
        Enter your PIN <br /> <NotLooking>(We're not looking)</NotLooking>
      </Title>
      <PinInput length={4} />
      <BaseButton txt="Enter" type="submit" />
    </Container>
  );
};

export default Pin;

const Image = styled("img")`
  animation: 3s float ease-in-out infinite;
  @keyframes float {
    0% {
      transform: translateY(0) rotate(0);
    }
    50% {
      transform: translateY(-5px) rotate(5deg);
    }
    100% {
      transform: translateY(0px) rotate(0);
    }
  }
`;

const NotLooking = styled("span")`
  font-size: 18px;
  color: ${({ theme }) => theme.palette.text.disabled};
  font-weight: 200;
`;

const Title = styled("h2")`
  text-align: center;
  color: ${({ theme }) => theme.palette.primary.contrastText};
  font-weight: 400;
`;

const Container = styled("form")`
  display: flex;
  position: relative;
  flex-direction: column;
  align-items: center;
  padding-top: 20vh;
  flex: 1;
  gap: 15px;
`;
