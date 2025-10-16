import { styled } from '@mui/material'
import './App.css'

function App() {

  return (
    <LayoutContainer>
      <MainContent>
        Hello
      </MainContent>
    </LayoutContainer>
  )
}

const LayoutContainer = styled("div")`
  min-height: 100vh;
  width: 100vw;
  display: flex;
  flex-direction: column;
`;

const MainContent = styled("main")`
  flex: 1;
  display: flex;
  background-color: red;
  justify-content: center;
  align-items: center;
`;

export default App
