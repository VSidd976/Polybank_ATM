import PinInput from "@components/PinInput/PinInput";
import NoPeeking from "@assets/no-peek.svg";
import { styled } from "@mui/material";
import BaseButton from "@components/Button/Button";

const Pin = () => {
  return (
    <Container>
      <Image src={NoPeeking} width={80} />
      <Title>
        Enter your PIN <br /> <NotLooking>(We're not looking)</NotLooking>
      </Title>
      <PinInput length={4} />
      <BaseButton txt="Enter" />
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

const Container = styled("div")`
  display: flex;
  position: relative;
  flex-direction: column;
  align-items: center;
  padding-top: 20vh;
  flex: 1;
  gap: 15px;
`;
