export const formatCardNumber = (number: string): string => {
  return number.replace(/(.{4})/g, "$1 ").trim();
};
