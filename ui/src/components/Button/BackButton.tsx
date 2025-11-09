import backIcon from "@assets/backArrow.svg";
import { styled } from "@mui/material";
import { withProps } from "@utils/withProps";
import BaseButton from "./Button";
import { useNavigate } from "react-router-dom";

const BackButtonStyled = styled(
  withProps(BaseButton, {
    variant: "rectangular",
    txt: "Back",
    startIcon: <img src={backIcon} alt="back" />,
  } as const),
)`
  position: absolute;
  top: 15px;
  left: 15px;
  padding: 25px;
  span[data-role="txt"] {
    font-size: 32px;
  }
`;

export const BackButton = ({
  className,
  disabled,
  onBeforeClick,
}: {
  className?: string;
  onBeforeClick?: () => void;
  disabled?: boolean;
}) => {
  const navigate = useNavigate();
  return (
    <BackButtonStyled
      className={className}
      disabled={disabled}
      onClick={async () => {
        onBeforeClick?.();
        navigate("/main");
      }}
    />
  );
};
