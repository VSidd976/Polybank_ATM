import { styled } from "@mui/material";

const BlackOutlined = styled("button")(({ theme }) => ({
  position: "relative",
  borderRadius: "20px",
  fontSize: "18px",
  lineHeight: "111%",
  padding: "9px 20px",
  fontWeight: 300,
  backgroundColor: theme.palette.background.paper,
  color: "#F8F0FB",
  border: "none",
  zIndex: 1,
  overflow: "hidden",
  cursor: "pointer",
  transition: "transform 0.1s ease-in-out",

  "&::before": {
    content: '""',
    position: "absolute",
    inset: 0,
    borderRadius: "20px",
    padding: "2px",
    background: `linear-gradient(270deg, ${theme.palette.secondary.main}, ${theme.palette.primary.light}, ${theme.palette.secondary.main})`,
    WebkitMask:
      "linear-gradient(#fff 0 0) content-box, linear-gradient(#fff 0 0)",
    WebkitMaskComposite: "xor",
    maskComposite: "exclude",
    zIndex: 0,
    backgroundSize: "600% 600%",
    animation: "gradientMove 4s linear infinite",
  },

  "&:hover": {
    transform: "scale(1.02)",
  },

  "&:active": {
    transform: "scale(0.98)",
    filter: "brightness(0.95)",
  },

  "@keyframes gradientMove": {
    "0%": {
      backgroundPosition: "0% 50%",
    },
    "50%": {
      backgroundPosition: "100% 50%",
    },
    "100%": {
      backgroundPosition: "0% 50%",
    },
  },
}));

export type ButtonVariant = keyof typeof ButtonVariantStyles;

export const ButtonVariantStyles = {
  "black-outlined": BlackOutlined,
} as const;
