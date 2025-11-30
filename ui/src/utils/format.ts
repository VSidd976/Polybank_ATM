export const formatCardNumber = (number: string): string => {
  return number.replace(/(.{4})/g, "$1 ").trim();
};

export const formatDate = (startDate: string): string => {
  return startDate.slice(0, startDate.indexOf("T")).replaceAll("-", ".");
};
