import { styled } from "@mui/material";
import type { PropsWithChildren } from "react";

type Props = { isAnimated: boolean } & PropsWithChildren;

const InOutContainer = ({ children, isAnimated }: Props) => {
  return <Container $animate={isAnimated}>{children}</Container>;
};

export default InOutContainer;

const Container = styled("div")<{ $animate: boolean }>`
  z-index: 1;
  ${({ $animate }) =>
    $animate ? `animation: rotateAndFloat 3.5s ease-in forwards;` : ""}

  @keyframes rotateAndFloat {
    0% {
      transform: translate(0, 0) rotate(0deg);
      opacity: 1;
    }
    15% {
      transform: translate(0, -120px) rotate(0deg);
      opacity: 1;
    }
    30% {
      transform: translate(20px, -120px) rotate(90deg);
      opacity: 1;
    }
    100% {
      transform: translate(40px, -150vh) rotate(90deg);
      opacity: 0;
    }
  }
`;
